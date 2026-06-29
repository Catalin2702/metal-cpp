/*
 *
 * Copyright 2020-2021 Apple Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// AppKit/NSScreen.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AppKitPrivate.hpp"
#include "NSColorSpace.hpp"

#include "Foundation/Foundation.hpp"

#include <cstdint>

namespace CA {
	class DisplayLink;
}

namespace NS {

struct EdgeInsets {
	CGFloat top;
	CGFloat left;
	CGFloat bottom;
	CGFloat right;
} _NS_PACKED;

using WindowDepth = std::int32_t;

_NS_OPTIONS(unsigned long long, AlignmentOptions) {
	AlignMinXInward    = 1ULL << 0,
	AlignMinYInward    = 1ULL << 1,
	AlignMaxXInward    = 1ULL << 2,
	AlignMaxYInward    = 1ULL << 3,
	AlignWidthInward   = 1ULL << 4,
	AlignHeightInward  = 1ULL << 5,

	AlignMinXOutward   = 1ULL << 8,
	AlignMinYOutward   = 1ULL << 9,
	AlignMaxXOutward   = 1ULL << 10,
	AlignMaxYOutward   = 1ULL << 11,
	AlignWidthOutward  = 1ULL << 12,
	AlignHeightOutward = 1ULL << 13,

	AlignMinXNearest   = 1ULL << 16,
	AlignMinYNearest   = 1ULL << 17,
	AlignMaxXNearest   = 1ULL << 18,
	AlignMaxYNearest   = 1ULL << 19,
	AlignWidthNearest  = 1ULL << 20,
	AlignHeightNearest = 1ULL << 21,

	AlignRectFlipped   = 1ULL << 63,

	AlignAllEdgesInward  = AlignMinXInward | AlignMaxXInward | AlignMinYInward | AlignMaxYInward,
	AlignAllEdgesOutward = AlignMinXOutward | AlignMaxXOutward | AlignMinYOutward | AlignMaxYOutward,
	AlignAllEdgesNearest = AlignMinXNearest | AlignMaxXNearest | AlignMinYNearest | AlignMaxYNearest,
};

class Screen: public Referencing<Screen> {
public:
	static Screen* mainScreen();
	static Screen* deepestScreen();
	static Array* screens();

public:
	[[nodiscard]] CGRect frame() const;
	[[nodiscard]] CGRect visibleFrame() const;
	[[nodiscard]] EdgeInsets safeAreaInsets() const;
	[[nodiscard]] CGRect auxiliaryTopLeftArea() const;
	[[nodiscard]] CGRect auxiliaryTopRightArea() const;

	[[nodiscard]] CGFloat backingScaleFactor() const;
	[[nodiscard]] String* localizedName() const;
	[[nodiscard]] Dictionary* deviceDescription() const;
	[[nodiscard]] ColorSpace* colorSpace() const;
	[[nodiscard]] Integer maximumFramesPerSecond() const;

	[[nodiscard]] WindowDepth depth() const;
	[[nodiscard]] const WindowDepth* supportedWindowDepths() const;

	[[nodiscard]] CGFloat maximumExtendedDynamicRangeColorComponentValue() const;
	[[nodiscard]] CGFloat maximumPotentialExtendedDynamicRangeColorComponentValue() const;
	[[nodiscard]] CGFloat maximumReferenceExtendedDynamicRangeColorComponentValue() const;

	[[nodiscard]] CGRect convertRectToBacking(const CGRect& rect) const;
	[[nodiscard]] CGRect convertRectFromBacking(const CGRect& rect) const;
	[[nodiscard]] CGRect backingAlignedRect(const CGRect& rect, AlignmentOptions options) const;

	// Creates a display link tied to this screen's display. The link invokes
	// 'selector' on 'pTarget' each vsync; the method must have the signature
	// (void)selector:(CA::DisplayLink*). Add it to a run loop to start it.
	[[nodiscard]] CA::DisplayLink* displayLink(const Object* pTarget, SEL selector) const;
};

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_NS_INLINE NS::Screen* NS::Screen::mainScreen() {
	return sendMessage<Screen*>(_APPKIT_PRIVATE_CLS(NSScreen), _APPKIT_PRIVATE_SEL(mainScreen));
}

_NS_INLINE NS::Screen* NS::Screen::deepestScreen() {
	return sendMessage<Screen*>(_APPKIT_PRIVATE_CLS(NSScreen), _APPKIT_PRIVATE_SEL(deepestScreen));
}

_NS_INLINE NS::Array* NS::Screen::screens() {
	return sendMessage<Array*>(_APPKIT_PRIVATE_CLS(NSScreen), _APPKIT_PRIVATE_SEL(screens));
}

_NS_INLINE CGRect NS::Screen::frame() const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(frame));
}

_NS_INLINE CGRect NS::Screen::visibleFrame() const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(visibleFrame));
}

_NS_INLINE NS::EdgeInsets NS::Screen::safeAreaInsets() const {
	return sendMessage<EdgeInsets>(this, _APPKIT_PRIVATE_SEL(safeAreaInsets));
}

_NS_INLINE CGRect NS::Screen::auxiliaryTopLeftArea() const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(auxiliaryTopLeftArea));
}

_NS_INLINE CGRect NS::Screen::auxiliaryTopRightArea() const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(auxiliaryTopRightArea));
}

_NS_INLINE CGFloat NS::Screen::backingScaleFactor() const {
	return sendMessage<CGFloat>(this, _APPKIT_PRIVATE_SEL(backingScaleFactor));
}

_NS_INLINE NS::String* NS::Screen::localizedName() const {
	return sendMessage<String*>(this, _APPKIT_PRIVATE_SEL(localizedName));
}

_NS_INLINE NS::Dictionary* NS::Screen::deviceDescription() const {
	return sendMessage<Dictionary*>(this, _APPKIT_PRIVATE_SEL(deviceDescription));
}

_NS_INLINE NS::ColorSpace* NS::Screen::colorSpace() const {
	return sendMessage<ColorSpace*>(this, _APPKIT_PRIVATE_SEL(colorSpace));
}

_NS_INLINE NS::Integer NS::Screen::maximumFramesPerSecond() const {
	return sendMessage<Integer>(this, _APPKIT_PRIVATE_SEL(maximumFramesPerSecond));
}

_NS_INLINE NS::WindowDepth NS::Screen::depth() const {
	return sendMessage<WindowDepth>(this, _APPKIT_PRIVATE_SEL(depth));
}

_NS_INLINE const NS::WindowDepth* NS::Screen::supportedWindowDepths() const {
	return sendMessage<const WindowDepth*>(this, _APPKIT_PRIVATE_SEL(supportedWindowDepths));
}

_NS_INLINE CGFloat NS::Screen::maximumExtendedDynamicRangeColorComponentValue() const {
	return sendMessage<CGFloat>(this, _APPKIT_PRIVATE_SEL(maximumExtendedDynamicRangeColorComponentValue));
}

_NS_INLINE CGFloat NS::Screen::maximumPotentialExtendedDynamicRangeColorComponentValue() const {
	return sendMessage<CGFloat>(this, _APPKIT_PRIVATE_SEL(maximumPotentialExtendedDynamicRangeColorComponentValue));
}

_NS_INLINE CGFloat NS::Screen::maximumReferenceExtendedDynamicRangeColorComponentValue() const {
	return sendMessage<CGFloat>(this, _APPKIT_PRIVATE_SEL(maximumReferenceExtendedDynamicRangeColorComponentValue));
}

_NS_INLINE CGRect NS::Screen::convertRectToBacking(const CGRect& rect) const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(convertRectToBacking_), rect);
}

_NS_INLINE CGRect NS::Screen::convertRectFromBacking(const CGRect& rect) const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(convertRectFromBacking_), rect);
}

_NS_INLINE CGRect NS::Screen::backingAlignedRect(const CGRect& rect, const AlignmentOptions options) const {
	return sendMessage<CGRect>(this, _APPKIT_PRIVATE_SEL(backingAlignedRect_options_), rect, options);
}

_NS_INLINE CA::DisplayLink* NS::Screen::displayLink(const Object* pTarget, SEL selector) const {
	return sendMessage<CA::DisplayLink*>(this, _APPKIT_PRIVATE_SEL(displayLinkWithTarget_selector_), pTarget, selector);
}
