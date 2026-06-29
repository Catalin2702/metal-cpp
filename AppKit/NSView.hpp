/*
 *
 * Copyright 2020-2021 Apple Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// AppKit/NSView.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

// ReSharper disable once CppUnusedIncludeDirective
#include "AppKitPrivate.hpp"
#include "Foundation/NSObject.hpp"
#include "Foundation/NSNumber.hpp"

#include <CoreGraphics/CGGeometry.h>
#include <objc/message.h>

namespace CA {
	class MetalLayer;
	class DisplayLink;
}

namespace NS
{
	class Event;

	// Receives the input events forwarded from an NS::View. Subclass it, override
	// the handlers you need, and attach an instance with View::setEventDispatcher().
	// The view retains the wrapper that holds the pointer, but does not own the C++
	// object, so the dispatcher must outlive the view.
	class ViewInputDispatcher
	{
		public:
			virtual ~ViewInputDispatcher() = default;

			virtual void DispatchMouseDown( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchMouseUp( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchMouseDragged( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchRightMouseDown( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchRightMouseUp( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchRightMouseDragged( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchOtherMouseDown( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchOtherMouseUp( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchOtherMouseDragged( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchMouseMoved( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchMouseEntered( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchMouseExited( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchKeyDown( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchKeyUp( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchFlagsChanged( [[maybe_unused]] Event* pEvent ) { }
			virtual void DispatchScrollWheel( [[maybe_unused]] Event* pEvent ) { }
	};

	class View : public NS::Referencing< View >
	{
		public:
			static View* alloc();
			[[nodiscard]] View*	init(const CGRect& frame) const;
			void setLayer(CA::MetalLayer* layer) const;
			void setOpaque(bool opaque) const;
			void setWantsLayer(bool wantsLayer) const;

			// Creates a display link tied to this view's display. The link invokes
			// 'selector' on 'pTarget' each vsync; the method must have the signature
			// (void)selector:(CA::DisplayLink*). Add it to a run loop to start it.
			[[nodiscard]] CA::DisplayLink* displayLink(const Object* pTarget, SEL selector) const;

			// --- Input handling -------------------------------------------------
			// Attach a dispatcher that receives this view's mouse / keyboard /
			// scroll events. The first call also installs the NSResponder methods
			// on the view's Objective-C class, so no manual registration is needed.
			void setEventDispatcher(const ViewInputDispatcher* pDispatcher) const;
			[[nodiscard]] ViewInputDispatcher* eventDispatcher() const;

			// Installs the mouse / keyboard / scroll NSResponder methods on this
			// view's class. Idempotent; normally triggered for you by
			// setEventDispatcher(), but you may call it explicitly (e.g. from a
			// derived view's init) to wire input up front. Each installed method
			// forwards its NS::Event to the attached dispatcher, e.g.
			// mouseDown: -> dispatcher->DispatchMouseDown().
			static void registerInputHandlers(const View* pView);
	};
}

_NS_INLINE NS::View* NS::View::alloc() {
	return Object::sendMessage< View* >( _APPKIT_PRIVATE_CLS( NSView ), _APPKIT_PRIVATE_SEL( alloc ) );
}

_NS_INLINE NS::View* NS::View::init(const CGRect& frame) const {
	return Object::sendMessage< View* >( this, _APPKIT_PRIVATE_SEL( initWithFrame_ ), frame );
}

_NS_INLINE void NS::View::setLayer(CA::MetalLayer* layer) const {
	return Object::sendMessage< void >( this, _APPKIT_PRIVATE_SEL( setLayer_ ), layer );
}

_NS_INLINE void NS::View::setOpaque(const bool opaque) const {
	return Object::sendMessage< void >( this, _APPKIT_PRIVATE_SEL( setOpaque_ ), opaque );
}

_NS_INLINE void NS::View::setWantsLayer(const bool wantsLayer) const {
	return Object::sendMessage< void >( this, _APPKIT_PRIVATE_SEL( setWantsLayer_ ), wantsLayer );
}

_NS_INLINE CA::DisplayLink* NS::View::displayLink(const Object* pTarget, SEL selector) const {
	return Object::sendMessage< CA::DisplayLink* >( this, _APPKIT_PRIVATE_SEL( displayLinkWithTarget_selector_ ), pTarget, selector );
}

// Process-wide, stable key for the associated dispatcher wrapper. Interned
// selectors are unique per name across translation units, so using one as the
// association key keeps setEventDispatcher()/eventDispatcher() in sync.
namespace NS::Private {
	_NS_INLINE const void* viewEventDispatcherKey() {
		return reinterpret_cast< const void* >( sel_registerName( "metalcpp_NSView_eventDispatcher" ) );
	}
}

_NS_INLINE void NS::View::setEventDispatcher(const ViewInputDispatcher* pDispatcher) const {
	registerInputHandlers( this );

	Value* pWrapper = Value::value( pDispatcher );
#ifdef __OBJC__
	objc_setAssociatedObject( (__bridge id)this, Private::viewEventDispatcherKey(), (__bridge id)pWrapper, OBJC_ASSOCIATION_RETAIN_NONATOMIC );
#else
	objc_setAssociatedObject( (id)this, Private::viewEventDispatcherKey(), (id)pWrapper, OBJC_ASSOCIATION_RETAIN_NONATOMIC );
#endif
}

_NS_INLINE NS::ViewInputDispatcher* NS::View::eventDispatcher() const {
#ifdef __OBJC__
	Value* pWrapper = (__bridge Value*)objc_getAssociatedObject( (__bridge id)this, Private::viewEventDispatcherKey() );
#else
	Value* pWrapper = (Value*)objc_getAssociatedObject( (id)this, Private::viewEventDispatcherKey() );
#endif
	return pWrapper ? reinterpret_cast< ViewInputDispatcher* >( pWrapper->pointerValue() ) : nullptr;
}

namespace NS::Private {
	// Installs one NSResponder method on pViewClass that forwards the event to
	// pMethod on the view's dispatcher; when no dispatcher is attached it calls the
	// superclass implementation, so views of this class that don't use a dispatcher
	// keep their default AppKit behaviour instead of swallowing the event. A block
	// IMP is used so the owning class is captured (needed for a correct super call).
	// Idempotent: a spare IMP is dropped if the class already implements the method.
	// '::Class' is qualified because NS::Private also contains a 'Class' namespace
	// (the runtime class-symbol table), which would otherwise shadow the type.
	_NS_INLINE void installViewResponder(::Class pViewClass, ::Class pSuperClass, const char* pSelectorName,
										 void (ViewInputDispatcher::* pMethod)(Event*)) {
		SEL sel = sel_registerName( pSelectorName );

		void (^block)(View*, Event*) = ^(View* pSelf, Event* pEvent) {
			if ( ViewInputDispatcher* pDispatcher = pSelf->eventDispatcher() ) {
				(pDispatcher->*pMethod)( pEvent );
			} else {
#ifdef __OBJC__
				struct objc_super super = { (__bridge id)pSelf, pSuperClass };
#else
				struct objc_super super = { (id)pSelf, pSuperClass };
#endif
				reinterpret_cast< void (*)(struct objc_super*, SEL, Event*) >( objc_msgSendSuper )( &super, sel, pEvent );
			}
		};

#ifdef __OBJC__
		const IMP imp = imp_implementationWithBlock( block );
#else
		const IMP imp = imp_implementationWithBlock( reinterpret_cast< id >( block ) );
#endif
		if ( !class_addMethod( pViewClass, sel, imp, "v@:@" ) ) {
			imp_removeBlock( imp );
		}
	}
}

_NS_INLINE void NS::View::registerInputHandlers(const View* pView) {
#ifdef __OBJC__
	Class viewClass = object_getClass( (__bridge id)pView );
#else
	Class viewClass = object_getClass( (id)pView );
#endif
	Class superClass = class_getSuperclass( viewClass );

	using D = ViewInputDispatcher;
	Private::installViewResponder( viewClass, superClass, "mouseDown:",         &D::DispatchMouseDown );
	Private::installViewResponder( viewClass, superClass, "mouseUp:",           &D::DispatchMouseUp );
	Private::installViewResponder( viewClass, superClass, "mouseDragged:",      &D::DispatchMouseDragged );
	Private::installViewResponder( viewClass, superClass, "rightMouseDown:",    &D::DispatchRightMouseDown );
	Private::installViewResponder( viewClass, superClass, "rightMouseUp:",      &D::DispatchRightMouseUp );
	Private::installViewResponder( viewClass, superClass, "rightMouseDragged:", &D::DispatchRightMouseDragged );
	Private::installViewResponder( viewClass, superClass, "otherMouseDown:",    &D::DispatchOtherMouseDown );
	Private::installViewResponder( viewClass, superClass, "otherMouseUp:",      &D::DispatchOtherMouseUp );
	Private::installViewResponder( viewClass, superClass, "otherMouseDragged:", &D::DispatchOtherMouseDragged );
	Private::installViewResponder( viewClass, superClass, "mouseMoved:",        &D::DispatchMouseMoved );
	Private::installViewResponder( viewClass, superClass, "mouseEntered:",      &D::DispatchMouseEntered );
	Private::installViewResponder( viewClass, superClass, "mouseExited:",       &D::DispatchMouseExited );
	Private::installViewResponder( viewClass, superClass, "keyDown:",           &D::DispatchKeyDown );
	Private::installViewResponder( viewClass, superClass, "keyUp:",             &D::DispatchKeyUp );
	Private::installViewResponder( viewClass, superClass, "flagsChanged:",      &D::DispatchFlagsChanged );
	Private::installViewResponder( viewClass, superClass, "scrollWheel:",       &D::DispatchScrollWheel );
}
