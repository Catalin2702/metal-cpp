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
// AppKit/NSWindow.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AppKitPrivate.hpp"
#include "NSView.hpp"

#include "Foundation/NSObject.hpp"

namespace CA {
class DisplayLink;
}

namespace NS {
class Screen;
}

namespace NS {

// NSWindowLevel is a typed NSInteger. Common values: Normal = 0, Floating = 3,
// ModalPanel = 8, MainMenu = 24, Status = 25, PopUpMenu = 101, ScreenSaver = 1000.
using WindowLevel = Integer;

_NS_OPTIONS(NS::UInteger, WindowCollectionBehavior) {
	WindowCollectionBehaviorDefault = 0,
	WindowCollectionBehaviorCanJoinAllSpaces = (1 << 0),
	WindowCollectionBehaviorMoveToActiveSpace = (1 << 1),
	WindowCollectionBehaviorManaged = (1 << 2),
	WindowCollectionBehaviorTransient = (1 << 3),
	WindowCollectionBehaviorStationary = (1 << 4),
	WindowCollectionBehaviorParticipatesInCycle = (1 << 5),
	WindowCollectionBehaviorIgnoresCycle = (1 << 6),
	WindowCollectionBehaviorFullScreenPrimary = (1 << 7),
	WindowCollectionBehaviorFullScreenAuxiliary = (1 << 8),
	WindowCollectionBehaviorFullScreenNone = (1 << 9),
	WindowCollectionBehaviorFullScreenAllowsTiling = (1 << 11),
	WindowCollectionBehaviorFullScreenDisallowsTiling = (1 << 12),
	WindowCollectionBehaviorPrimary = (1 << 16),
	WindowCollectionBehaviorAuxiliary = (1 << 17),
	WindowCollectionBehaviorCanJoinAllApplications = (1 << 18),
};

class Window : public Referencing<Window> {
public:
	static Window* alloc();
	void close() const;
	[[nodiscard]] Window* init(const CGRect& contentRect, WindowStyleMask styleMask, BackingStoreType backing, bool defer) const;

	void makeKeyAndOrderFront(const Object* pSender) const;

public:
	void setContentView(const View* pContentView) const;
	void setDelegate(const Object* pDelegate) const;
	void setFrameAutosaveName(const String* pName) const;
	void setFrameUsingName(const String* pName) const;
	void setFrame(const CGRect& frame, bool display = true) const;
	void setFrame(const CGRect& frame, bool display, bool animate) const;
	void setMinSize(const CGSize& minSize) const;
	void setOpaque(bool flag) const;
	void setTitle(const String* pTitle) const;

public:
	void setStyleMask(WindowStyleMask styleMask) const;
	void setLevel(WindowLevel level) const;
	void setCollectionBehavior(WindowCollectionBehavior behavior) const;
	void setAcceptsMouseMovedEvents(bool flag) const;
	void setContentViewController(const Object* pController) const;

	void center() const;
	void miniaturize(const Object* pSender) const;
	void toggleFullScreen(const Object* pSender) const;

public:
	[[nodiscard]] CGFloat backingScaleFactor() const;
	[[nodiscard]] CGRect contentRectForFrameRect(const CGRect& frameRect) const;
	[[nodiscard]] CGRect contentRectForFrameRect() const;
	[[nodiscard]] CGRect contentLayoutRect() const;
	[[nodiscard]] View* contentView() const;
	[[nodiscard]] Object* contentViewController() const;
	[[nodiscard]] Object* delegate() const;
	[[nodiscard]] CGRect frame() const;
	[[nodiscard]] CGSize minSize() const;
	[[nodiscard]] WindowStyleMask styleMask() const;
	[[nodiscard]] WindowLevel level() const;
	[[nodiscard]] WindowCollectionBehavior collectionBehavior() const;
	[[nodiscard]] bool acceptsMouseMovedEvents() const;
	[[nodiscard]] Screen* screen() const;
	[[nodiscard]] String* title() const;

	// Creates a display link tied to this window's display. The link invokes
	// 'selector' on 'pTarget' each vsync; the method must have the signature
	// (void)selector:(CA::DisplayLink*). Add it to a run loop to start it.
	[[nodiscard]] CA::DisplayLink* displayLink(const Object* pTarget, SEL selector) const;
};

}


_NS_INLINE NS::Window* NS::Window::alloc() {
	return sendMessage<Window*>(_APPKIT_PRIVATE_CLS(NSWindow), _NS_PRIVATE_SEL(alloc));
}

_NS_INLINE void NS::Window::close() const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(close));
}

_NS_INLINE NS::Window* NS::Window::init(const CGRect& contentRect, const WindowStyleMask styleMask, const BackingStoreType backing, const bool defer) const {
	return sendMessage<Window*>(this, _APPKIT_PRIVATE_SEL(initWithContentRect_styleMask_backing_defer_), contentRect, styleMask, backing, defer);
}

_NS_INLINE void NS::Window::makeKeyAndOrderFront(const Object* pSender) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(makeKeyAndOrderFront_), pSender);
}

_NS_INLINE void NS::Window::setContentView(const View* pContentView) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setContentView_), pContentView);
}

_NS_INLINE void NS::Window::setDelegate(const Object* pDelegate) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setDelegate_), pDelegate);
}

_NS_INLINE void NS::Window::setFrameAutosaveName(const String* pName) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setFrameAutosaveName_), pName);
}

_NS_INLINE void NS::Window::setFrameUsingName(const String* pName) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setFrameUsingName_), pName);
}

_NS_INLINE void NS::Window::setFrame(const CGRect& frame, const bool display) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setFrame_display_), frame, display);
}

_NS_INLINE void NS::Window::setFrame(const CGRect& frame, const bool display, const bool animate) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setFrame_display_animate_), frame, display, animate);
}

_NS_INLINE void NS::Window::setMinSize(const CGSize& minSize) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setMinSize_), minSize);
}

_NS_INLINE void NS::Window::setOpaque(const bool flag) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setOpaque_), flag);
}

_NS_INLINE void NS::Window::setTitle(const String* pTitle) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setTitle_), pTitle);
}

_NS_INLINE void NS::Window::setStyleMask(const WindowStyleMask styleMask) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setStyleMask_), styleMask);
}

_NS_INLINE void NS::Window::setLevel(const WindowLevel level) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setLevel_), level);
}

_NS_INLINE void NS::Window::setCollectionBehavior(const WindowCollectionBehavior behavior) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setCollectionBehavior_), behavior);
}

_NS_INLINE void NS::Window::setAcceptsMouseMovedEvents(const bool flag) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setAcceptsMouseMovedEvents_), flag);
}

_NS_INLINE void NS::Window::setContentViewController(const Object* pController) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(setContentViewController_), pController);
}

_NS_INLINE void NS::Window::center() const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(center));
}

_NS_INLINE void NS::Window::miniaturize(const Object* pSender) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(miniaturize_), pSender);
}

_NS_INLINE void NS::Window::toggleFullScreen(const Object* pSender) const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(toggleFullScreen_), pSender);
}

_NS_INLINE CGFloat NS::Window::backingScaleFactor() const {
	return sendMessage<CGFloat>(this, _APPKIT_PRIVATE_SEL(backingScaleFactor));
}

_NS_INLINE CGRect NS::Window::contentRectForFrameRect(const CGRect& frameRect) const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(contentRectForFrameRect_), frameRect);
}

_NS_INLINE CGRect NS::Window::contentRectForFrameRect() const {
	return contentRectForFrameRect(frame());
}

_NS_INLINE CGRect NS::Window::contentLayoutRect() const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(contentLayoutRect));
}

_NS_INLINE NS::View* NS::Window::contentView() const {
	return sendMessage<View*>(this, _APPKIT_PRIVATE_SEL(contentView));
}

_NS_INLINE NS::Object* NS::Window::contentViewController() const {
	return sendMessage<Object*>(this, _APPKIT_PRIVATE_SEL(contentViewController));
}

_NS_INLINE NS::Object* NS::Window::delegate() const {
	return sendMessage<Object*>(this, _APPKIT_PRIVATE_SEL(delegate));
}

_NS_INLINE CGRect NS::Window::frame() const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(frame));
}

_NS_INLINE CGSize NS::Window::minSize() const {
	return sendMessage<CGSize>(this, _APPKIT_PRIVATE_SEL(minSize));
}

_NS_INLINE NS::WindowStyleMask NS::Window::styleMask() const {
	return sendMessage<WindowStyleMask>(this, _APPKIT_PRIVATE_SEL(styleMask));
}

_NS_INLINE NS::WindowLevel NS::Window::level() const {
	return sendMessage<WindowLevel>(this, _APPKIT_PRIVATE_SEL(level));
}

_NS_INLINE NS::WindowCollectionBehavior NS::Window::collectionBehavior() const {
	return sendMessage<WindowCollectionBehavior>(this, _APPKIT_PRIVATE_SEL(collectionBehavior));
}

_NS_INLINE bool NS::Window::acceptsMouseMovedEvents() const {
	return sendMessage<bool>(this, _APPKIT_PRIVATE_SEL(acceptsMouseMovedEvents));
}

_NS_INLINE NS::Screen* NS::Window::screen() const {
	return sendMessage<Screen*>(this, _APPKIT_PRIVATE_SEL(screen));
}

_NS_INLINE NS::String* NS::Window::title() const {
	return sendMessage<String*>(this, _APPKIT_PRIVATE_SEL(title_));
}

_NS_INLINE CA::DisplayLink* NS::Window::displayLink(const Object* pTarget, SEL selector) const {
	return sendMessage<CA::DisplayLink*>(this, _APPKIT_PRIVATE_SEL(displayLinkWithTarget_selector_), pTarget, selector);
}
