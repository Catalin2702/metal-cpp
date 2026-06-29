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
// AppKit/NSColorSpace.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AppKitPrivate.hpp"

#include "Foundation/Foundation.hpp"

namespace NS {

_NS_ENUM(NS::Integer, ColorSpaceModel) {
	ColorSpaceModelUnknown   = -1,
	ColorSpaceModelGray      = 0,
	ColorSpaceModelRGB       = 1,
	ColorSpaceModelCMYK      = 2,
	ColorSpaceModelLAB       = 3,
	ColorSpaceModelDeviceN   = 4,
	ColorSpaceModelIndexed   = 5,
	ColorSpaceModelPatterned = 6,
};

class ColorSpace: public Referencing<ColorSpace> {
public:
	static ColorSpace* sRGBColorSpace();
	static ColorSpace* extendedSRGBColorSpace();
	static ColorSpace* displayP3ColorSpace();
	static ColorSpace* adobeRGB1998ColorSpace();
	static ColorSpace* genericRGBColorSpace();
	static ColorSpace* deviceRGBColorSpace();

public:
	[[nodiscard]] String*          localizedName() const;
	[[nodiscard]] Integer          numberOfColorComponents() const;
	[[nodiscard]] ColorSpaceModel  colorSpaceModel() const;
};

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_NS_INLINE NS::ColorSpace* NS::ColorSpace::sRGBColorSpace() {
	return sendMessage<ColorSpace*>(_APPKIT_PRIVATE_CLS(NSColorSpace), _APPKIT_PRIVATE_SEL(sRGBColorSpace));
}

_NS_INLINE NS::ColorSpace* NS::ColorSpace::extendedSRGBColorSpace() {
	return sendMessage<ColorSpace*>(_APPKIT_PRIVATE_CLS(NSColorSpace), _APPKIT_PRIVATE_SEL(extendedSRGBColorSpace));
}

_NS_INLINE NS::ColorSpace* NS::ColorSpace::displayP3ColorSpace() {
	return sendMessage<ColorSpace*>(_APPKIT_PRIVATE_CLS(NSColorSpace), _APPKIT_PRIVATE_SEL(displayP3ColorSpace));
}

_NS_INLINE NS::ColorSpace* NS::ColorSpace::adobeRGB1998ColorSpace() {
	return sendMessage<ColorSpace*>(_APPKIT_PRIVATE_CLS(NSColorSpace), _APPKIT_PRIVATE_SEL(adobeRGB1998ColorSpace));
}

_NS_INLINE NS::ColorSpace* NS::ColorSpace::genericRGBColorSpace() {
	return sendMessage<ColorSpace*>(_APPKIT_PRIVATE_CLS(NSColorSpace), _APPKIT_PRIVATE_SEL(genericRGBColorSpace));
}

_NS_INLINE NS::ColorSpace* NS::ColorSpace::deviceRGBColorSpace() {
	return sendMessage<ColorSpace*>(_APPKIT_PRIVATE_CLS(NSColorSpace), _APPKIT_PRIVATE_SEL(deviceRGBColorSpace));
}

_NS_INLINE NS::String* NS::ColorSpace::localizedName() const {
	return sendMessage<String*>(this, _APPKIT_PRIVATE_SEL(localizedName));
}

_NS_INLINE NS::Integer NS::ColorSpace::numberOfColorComponents() const {
	return sendMessage<Integer>(this, _APPKIT_PRIVATE_SEL(numberOfColorComponents));
}

_NS_INLINE NS::ColorSpaceModel NS::ColorSpace::colorSpaceModel() const {
	return sendMessage<ColorSpaceModel>(this, _APPKIT_PRIVATE_SEL(colorSpaceModel));
}
