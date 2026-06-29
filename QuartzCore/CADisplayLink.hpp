//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// QuartzCore/CADisplayLink.hpp
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

#include "../Foundation/NSObject.hpp"
#include "../Foundation/NSTypes.hpp"

#include "CADefines.hpp"
#include "CAPrivate.hpp"

#include <CoreFoundation/CoreFoundation.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS
{
class RunLoop;
class String;
}

namespace CA
{

// Mirrors CAFrameRateRange { float minimum; float maximum; float preferred; }.
struct FrameRateRange
{
    float minimum;
    float maximum;
    float preferred;
} _CA_PACKED;

// A timer object that lets the engine synchronise its render loop to the
// display's refresh rate. On macOS a CADisplayLink is not created directly;
// obtain one from NS::View::displayLink(target, selector), add it to a run loop,
// and read timestamp()/targetTimestamp()/duration() inside the callback.
class DisplayLink : public NS::Referencing<DisplayLink>
{
public:
    void                 addToRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const;
    void                 removeFromRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const;
    void                 invalidate() const;

    CFTimeInterval       timestamp() const;
    CFTimeInterval       duration() const;
    CFTimeInterval       targetTimestamp() const;

    bool                 isPaused() const;
    void                 setPaused(bool paused) const;

    FrameRateRange       preferredFrameRateRange() const;
    void                 setPreferredFrameRateRange(FrameRateRange range) const;
};

} // namespace CA

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_CA_INLINE void CA::DisplayLink::addToRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(addToRunLoop_forMode_), pRunLoop, pMode);
}

_CA_INLINE void CA::DisplayLink::removeFromRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(removeFromRunLoop_forMode_), pRunLoop, pMode);
}

_CA_INLINE void CA::DisplayLink::invalidate() const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(invalidate));
}

_CA_INLINE CFTimeInterval CA::DisplayLink::timestamp() const
{
    return Object::sendMessage<CFTimeInterval>(this, _CA_PRIVATE_SEL(timestamp));
}

_CA_INLINE CFTimeInterval CA::DisplayLink::duration() const
{
    return Object::sendMessage<CFTimeInterval>(this, _CA_PRIVATE_SEL(duration));
}

_CA_INLINE CFTimeInterval CA::DisplayLink::targetTimestamp() const
{
    return Object::sendMessage<CFTimeInterval>(this, _CA_PRIVATE_SEL(targetTimestamp));
}

_CA_INLINE bool CA::DisplayLink::isPaused() const
{
    return Object::sendMessage<bool>(this, _CA_PRIVATE_SEL(isPaused));
}

_CA_INLINE void CA::DisplayLink::setPaused(bool paused) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setPaused_), paused);
}

_CA_INLINE CA::FrameRateRange CA::DisplayLink::preferredFrameRateRange() const
{
    return Object::sendMessage<FrameRateRange>(this, _CA_PRIVATE_SEL(preferredFrameRateRange));
}

_CA_INLINE void CA::DisplayLink::setPreferredFrameRateRange(FrameRateRange range) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setPreferredFrameRateRange_), range);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
