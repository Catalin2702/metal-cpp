//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Foundation/NSRunLoop.hpp
//
// Copyright 2020-2024 Apple Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "NSDefines.hpp"
#include "NSObject.hpp"
#include "NSPrivate.hpp"
#include "NSString.hpp"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{

class RunLoop : public Referencing<RunLoop>
{
public:
    static RunLoop* currentRunLoop();
    static RunLoop* mainRunLoop();

    // The default run-loop mode (NSDefaultRunLoopMode == "kCFRunLoopDefaultMode"),
    // suitable for CADisplayLink::addToRunLoop(). Returned autoreleased.
    static String*  defaultMode();
};

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_NS_INLINE NS::RunLoop* NS::RunLoop::currentRunLoop()
{
    return Object::sendMessage<RunLoop*>(_NS_PRIVATE_CLS(NSRunLoop), _NS_PRIVATE_SEL(currentRunLoop));
}

_NS_INLINE NS::RunLoop* NS::RunLoop::mainRunLoop()
{
    return Object::sendMessage<RunLoop*>(_NS_PRIVATE_CLS(NSRunLoop), _NS_PRIVATE_SEL(mainRunLoop));
}

_NS_INLINE NS::String* NS::RunLoop::defaultMode()
{
    return String::string("kCFRunLoopDefaultMode", UTF8StringEncoding);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
