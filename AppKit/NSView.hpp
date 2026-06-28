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

_NS_INLINE void NS::View::registerInputHandlers(const View* pView) {
#ifdef __OBJC__
	Class viewClass = object_getClass( (__bridge id)pView );
#else
	Class viewClass = object_getClass( (id)pView );
#endif

	// Each trampoline is captureless so it converts to an IMP. 'self' is the view;
	// it forwards the NSResponder event straight to the attached dispatcher (if
	// any). class_addMethod is a no-op when the class already implements the
	// selector, so this is idempotent.
	#define _NS_FWD_INPUT( objcSelector, dispatchMethod )                                          \
		do {                                                                                       \
			void (*fn)( View*, SEL, Event* ) = []( View* self, SEL, Event* pEvent ){               \
				if ( ViewInputDispatcher* pDispatcher = self->eventDispatcher() ) {                \
					pDispatcher->dispatchMethod( pEvent );                                         \
				}                                                                                  \
			};                                                                                     \
			class_addMethod( viewClass, sel_registerName( objcSelector ), (IMP)fn, "v@:@" );       \
		} while ( 0 )

	_NS_FWD_INPUT( "mouseDown:",         DispatchMouseDown );
	_NS_FWD_INPUT( "mouseUp:",           DispatchMouseUp );
	_NS_FWD_INPUT( "mouseDragged:",      DispatchMouseDragged );
	_NS_FWD_INPUT( "rightMouseDown:",    DispatchRightMouseDown );
	_NS_FWD_INPUT( "rightMouseUp:",      DispatchRightMouseUp );
	_NS_FWD_INPUT( "rightMouseDragged:", DispatchRightMouseDragged );
	_NS_FWD_INPUT( "otherMouseDown:",    DispatchOtherMouseDown );
	_NS_FWD_INPUT( "otherMouseUp:",      DispatchOtherMouseUp );
	_NS_FWD_INPUT( "otherMouseDragged:", DispatchOtherMouseDragged );
	_NS_FWD_INPUT( "mouseMoved:",        DispatchMouseMoved );
	_NS_FWD_INPUT( "mouseEntered:",      DispatchMouseEntered );
	_NS_FWD_INPUT( "mouseExited:",       DispatchMouseExited );
	_NS_FWD_INPUT( "keyDown:",           DispatchKeyDown );
	_NS_FWD_INPUT( "keyUp:",             DispatchKeyUp );
	_NS_FWD_INPUT( "flagsChanged:",      DispatchFlagsChanged );
	_NS_FWD_INPUT( "scrollWheel:",       DispatchScrollWheel );

	#undef _NS_FWD_INPUT
}
