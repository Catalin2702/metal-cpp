//-------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// QuartzCore/CAMetalDisplayLink.hpp
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

#include "../Foundation/NSNumber.hpp"
#include "../Foundation/NSObject.hpp"
#include "../Foundation/NSTypes.hpp"

#include "CADefines.hpp"
#include "CADisplayLink.hpp" // CA::FrameRateRange
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
class MetalDrawable;
class MetalLayer;
class MetalDisplayLink;

// Snapshot handed to the delegate each update: the drawable to render into and
// the timestamps the frame is expected to be presented at. Mirrors
// CAMetalDisplayLinkUpdate.
class MetalDisplayLinkUpdate : public NS::Referencing<MetalDisplayLinkUpdate>
{
public:
    MetalDrawable* drawable() const;
    CFTimeInterval targetTimestamp() const;
    CFTimeInterval targetPresentationTimestamp() const;
};

// Receives the per-frame callback of a CAMetalDisplayLink. Subclass it, override
// metalDisplayLinkNeedsUpdate() and attach it with MetalDisplayLink::setDelegate().
// The link retains the wrapper that holds the pointer but does not own the C++
// object, so the delegate must outlive the link.
class MetalDisplayLinkDelegate
{
public:
    virtual ~MetalDisplayLinkDelegate() = default;

    virtual void metalDisplayLinkNeedsUpdate([[maybe_unused]] MetalDisplayLink* pLink,
                                             [[maybe_unused]] MetalDisplayLinkUpdate* pUpdate) {}
};

// A display link that vends Metal drawables in step with the display refresh.
// Create one for a CAMetalLayer, set a delegate, then add it to a run loop.
class MetalDisplayLink : public NS::Referencing<MetalDisplayLink>
{
public:
    static MetalDisplayLink* alloc();
    MetalDisplayLink*        init(const MetalLayer* pLayer);

    void                     setDelegate(const MetalDisplayLinkDelegate* pDelegate) const;
    MetalDisplayLinkDelegate* delegate() const;

    void                     addToRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const;
    void                     removeFromRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const;
    void                     invalidate() const;

    bool                     isPaused() const;
    void                     setPaused(bool paused) const;

    NS::Integer              preferredFrameLatency() const;
    void                     setPreferredFrameLatency(NS::Integer latency) const;

    FrameRateRange           preferredFrameRateRange() const;
    void                     setPreferredFrameRateRange(FrameRateRange range) const;
};

} // namespace CA

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_CA_INLINE CA::MetalDrawable* CA::MetalDisplayLinkUpdate::drawable() const
{
    return Object::sendMessage<MetalDrawable*>(this, _CA_PRIVATE_SEL(drawable));
}

_CA_INLINE CFTimeInterval CA::MetalDisplayLinkUpdate::targetTimestamp() const
{
    return Object::sendMessage<CFTimeInterval>(this, _CA_PRIVATE_SEL(targetTimestamp));
}

_CA_INLINE CFTimeInterval CA::MetalDisplayLinkUpdate::targetPresentationTimestamp() const
{
    return Object::sendMessage<CFTimeInterval>(this, _CA_PRIVATE_SEL(targetPresentationTimestamp));
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

_CA_INLINE CA::MetalDisplayLink* CA::MetalDisplayLink::alloc()
{
    return NS::Object::alloc<MetalDisplayLink>(_CA_PRIVATE_CLS(CAMetalDisplayLink));
}

_CA_INLINE CA::MetalDisplayLink* CA::MetalDisplayLink::init(const MetalLayer* pLayer)
{
    return Object::sendMessage<MetalDisplayLink*>(this, _CA_PRIVATE_SEL(initWithMetalLayer_), pLayer);
}

_CA_INLINE void CA::MetalDisplayLink::setDelegate(const MetalDisplayLinkDelegate* pDelegate) const
{
    // Wrap the C++ delegate in an NSValue and register an Objective-C trampoline
    // on the NSValue class. It reads the delegate back through pointerValue() and
    // forwards the metalDisplayLink:needsUpdate: callback to the C++ object.
    NS::Value* pWrapper = NS::Value::value(pDelegate);

    void (*needsUpdate)(NS::Value*, SEL, CA::MetalDisplayLink*, CA::MetalDisplayLinkUpdate*) =
        [](NS::Value* pSelf, SEL, CA::MetalDisplayLink* pLink, CA::MetalDisplayLinkUpdate* pUpdate) {
            reinterpret_cast<MetalDisplayLinkDelegate*>(pSelf->pointerValue())->metalDisplayLinkNeedsUpdate(pLink, pUpdate);
        };

    class_addMethod((Class)objc_lookUpClass("NSValue"), sel_registerName("metalDisplayLink:needsUpdate:"), (IMP)needsUpdate, "v@:@@");

    // Keep the wrapper alive for as long as the dispatch needs it.
#ifdef __OBJC__
    objc_setAssociatedObject((__bridge id)pWrapper, "cametaldisplaylinkdelegate_cpp", (__bridge id)pWrapper, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
#else
    objc_setAssociatedObject((id)pWrapper, "cametaldisplaylinkdelegate_cpp", (id)pWrapper, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
#endif

    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setDelegate_), pWrapper);
}

_CA_INLINE CA::MetalDisplayLinkDelegate* CA::MetalDisplayLink::delegate() const
{
    NS::Value* pWrapper = Object::sendMessage<NS::Value*>(this, _CA_PRIVATE_SEL(delegate));
    return pWrapper ? reinterpret_cast<MetalDisplayLinkDelegate*>(pWrapper->pointerValue()) : nullptr;
}

_CA_INLINE void CA::MetalDisplayLink::addToRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(addToRunLoop_forMode_), pRunLoop, pMode);
}

_CA_INLINE void CA::MetalDisplayLink::removeFromRunLoop(const NS::RunLoop* pRunLoop, const NS::String* pMode) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(removeFromRunLoop_forMode_), pRunLoop, pMode);
}

_CA_INLINE void CA::MetalDisplayLink::invalidate() const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(invalidate));
}

_CA_INLINE bool CA::MetalDisplayLink::isPaused() const
{
    return Object::sendMessage<bool>(this, _CA_PRIVATE_SEL(isPaused));
}

_CA_INLINE void CA::MetalDisplayLink::setPaused(bool paused) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setPaused_), paused);
}

_CA_INLINE NS::Integer CA::MetalDisplayLink::preferredFrameLatency() const
{
    return Object::sendMessage<NS::Integer>(this, _CA_PRIVATE_SEL(preferredFrameLatency));
}

_CA_INLINE void CA::MetalDisplayLink::setPreferredFrameLatency(NS::Integer latency) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setPreferredFrameLatency_), latency);
}

_CA_INLINE CA::FrameRateRange CA::MetalDisplayLink::preferredFrameRateRange() const
{
    return Object::sendMessage<FrameRateRange>(this, _CA_PRIVATE_SEL(preferredFrameRateRange));
}

_CA_INLINE void CA::MetalDisplayLink::setPreferredFrameRateRange(FrameRateRange range) const
{
    Object::sendMessage<void>(this, _CA_PRIVATE_SEL(setPreferredFrameRateRange_), range);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------