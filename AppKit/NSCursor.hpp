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
// AppKit/NSCursor.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "AppKitPrivate.hpp"

#include "Foundation/NSObject.hpp"

namespace NS {

class Cursor: public Referencing<Cursor> {
public:
	static Cursor* currentCursor();
	static Cursor* arrowCursor();

	// Reference-counted show/hide. Each hide() must be balanced by an unhide().
	static void    hide();
	static void    unhide();
	static void    setHiddenUntilMouseMoves(bool flag);

public:
	void set() const;
	void push() const;
	void pop() const;
};

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_NS_INLINE NS::Cursor* NS::Cursor::currentCursor() {
	return sendMessage<Cursor*>(_APPKIT_PRIVATE_CLS(NSCursor), _APPKIT_PRIVATE_SEL(currentCursor));
}

_NS_INLINE NS::Cursor* NS::Cursor::arrowCursor() {
	return sendMessage<Cursor*>(_APPKIT_PRIVATE_CLS(NSCursor), _APPKIT_PRIVATE_SEL(arrowCursor));
}

_NS_INLINE void NS::Cursor::hide() {
	sendMessage<void>(_APPKIT_PRIVATE_CLS(NSCursor), _APPKIT_PRIVATE_SEL(hide));
}

_NS_INLINE void NS::Cursor::unhide() {
	sendMessage<void>(_APPKIT_PRIVATE_CLS(NSCursor), _APPKIT_PRIVATE_SEL(unhide));
}

_NS_INLINE void NS::Cursor::setHiddenUntilMouseMoves(const bool flag) {
	sendMessage<void>(_APPKIT_PRIVATE_CLS(NSCursor), _APPKIT_PRIVATE_SEL(setHiddenUntilMouseMoves_), flag);
}

_NS_INLINE void NS::Cursor::set() const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(set));
}

_NS_INLINE void NS::Cursor::push() const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(push));
}

_NS_INLINE void NS::Cursor::pop() const {
	sendMessage<void>(this, _APPKIT_PRIVATE_SEL(pop));
}
