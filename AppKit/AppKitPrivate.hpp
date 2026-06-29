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
// AppKit/AppKitPrivate.hpp
//
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma once

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <objc/runtime.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#define _APPKIT_PRIVATE_CLS( symbol )				   ( Private::Class::s_k ## symbol )
#define _APPKIT_PRIVATE_SEL( accessor )				 ( Private::Selector::s_k ## accessor )

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined( NS_PRIVATE_IMPLEMENTATION )

#define _APPKIT_PRIVATE_VISIBILITY						__attribute__( ( visibility( "default" ) ) )
#define _APPKIT_PRIVATE_IMPORT						  __attribute__( ( weak_import ) )

#if __OBJC__
#define  _APPKIT_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   ( ( __bridge void* ) objc_lookUpClass( # symbol ) )
#else
#define  _APPKIT_PRIVATE_OBJC_LOOKUP_CLASS( symbol  )   objc_lookUpClass( # symbol ) 
#endif // __OBJC__

#define _APPKIT_PRIVATE_DEF_CLS( symbol )				void*				   s_k ## symbol 	_NS_PRIVATE_VISIBILITY = _NS_PRIVATE_OBJC_LOOKUP_CLASS( symbol );
#define _APPKIT_PRIVATE_DEF_SEL( accessor, symbol )	 SEL					 s_k ## accessor	_NS_PRIVATE_VISIBILITY = sel_registerName( symbol );
#define _APPKIT_PRIVATE_DEF_CONST( type, symbol )	   _NS_EXTERN type const   NS ## symbol   _NS_PRIVATE_IMPORT; \
													type const			  NS::symbol	 = ( nullptr != &NS ## symbol ) ? NS ## symbol : nullptr;


#else

#define _APPKIT_PRIVATE_DEF_CLS( symbol )				extern void*			s_k ## symbol;
#define _APPKIT_PRIVATE_DEF_SEL( accessor, symbol )	 extern SEL			  s_k ## accessor;
#define _APPKIT_PRIVATE_DEF_CONST( type, symbol )


#endif // NS_PRIVATE_IMPLEMENTATION

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS::Private::Class {

_APPKIT_PRIVATE_DEF_CLS( NSApplication );
_APPKIT_PRIVATE_DEF_CLS( NSRunningApplication );
_APPKIT_PRIVATE_DEF_CLS( NSView );
_APPKIT_PRIVATE_DEF_CLS( NSOpenPanel );
_APPKIT_PRIVATE_DEF_CLS( NSSavePanel );
_APPKIT_PRIVATE_DEF_CLS( NSWindow );
_APPKIT_PRIVATE_DEF_CLS( NSMenu );
_APPKIT_PRIVATE_DEF_CLS( NSMenuItem );
_APPKIT_PRIVATE_DEF_CLS( NSEvent );
_APPKIT_PRIVATE_DEF_CLS( NSScreen );
_APPKIT_PRIVATE_DEF_CLS( NSColorSpace );
_APPKIT_PRIVATE_DEF_CLS( NSCursor );

} // Class

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

namespace NS::Private::Selector
{

_APPKIT_PRIVATE_DEF_SEL( addItem_,
						"addItem:" );

_APPKIT_PRIVATE_DEF_SEL( addItemWithTitle_action_keyEquivalent_,
						"addItemWithTitle:action:keyEquivalent:" );

_APPKIT_PRIVATE_DEF_SEL( applicationDidFinishLaunching_,
						"applicationDidFinishLaunching:" );

_APPKIT_PRIVATE_DEF_SEL( applicationShouldTerminateAfterLastWindowClosed_,
						"applicationShouldTerminateAfterLastWindowClosed:" );

_APPKIT_PRIVATE_DEF_SEL( applicationWillFinishLaunching_,
						"applicationWillFinishLaunching:" );

_APPKIT_PRIVATE_DEF_SEL( close,
						"close" );

_APPKIT_PRIVATE_DEF_SEL( backingScaleFactor,
						"backingScaleFactor" );

_APPKIT_PRIVATE_DEF_SEL(contentRectForFrameRect_,
						"contentRectForFrameRect:");

_APPKIT_PRIVATE_DEF_SEL( currentApplication,
						"currentApplication" );

_APPKIT_PRIVATE_DEF_SEL( keyEquivalentModifierMask,
 						"keyEquivalentModifierMask" );

_APPKIT_PRIVATE_DEF_SEL( localizedName,
						"localizedName" );

_APPKIT_PRIVATE_DEF_SEL( sharedApplication,
						"sharedApplication" );

_APPKIT_PRIVATE_DEF_SEL( delegate,
						"delegate" );

_APPKIT_PRIVATE_DEF_SEL( setDelegate_,
						"setDelegate:" );

_APPKIT_PRIVATE_DEF_SEL( setActivationPolicy_,
						"setActivationPolicy:" );

_APPKIT_PRIVATE_DEF_SEL(activationPolicy,
						"activationPolicy");

_APPKIT_PRIVATE_DEF_SEL( activateIgnoringOtherApps_,
						"activateIgnoringOtherApps:" );

_APPKIT_PRIVATE_DEF_SEL( run,
						"run" );

_APPKIT_PRIVATE_DEF_SEL( nextEventMatchingMask_untilDate_inMode_dequeue_,
						"nextEventMatchingMask:untilDate:inMode:dequeue:" );

_APPKIT_PRIVATE_DEF_SEL( sendEvent_,
						"sendEvent:" );

_APPKIT_PRIVATE_DEF_SEL(postEvent_atStart_,
						"postEvent:atStart:");

_APPKIT_PRIVATE_DEF_SEL( terminate_,
						"terminate:" );

_APPKIT_PRIVATE_DEF_SEL(stop_,
						"stop:");

_APPKIT_PRIVATE_DEF_SEL( initWithContentRect_styleMask_backing_defer_,
						"initWithContentRect:styleMask:backing:defer:" );

_APPKIT_PRIVATE_DEF_SEL( initWithFrame_,
						"initWithFrame:" );

_APPKIT_PRIVATE_DEF_SEL( frame,
						"frame" );

_APPKIT_PRIVATE_DEF_SEL( initWithTitle_,
						"initWithTitle:" );

_APPKIT_PRIVATE_DEF_SEL( setLayer_,
						"setLayer:" );

_APPKIT_PRIVATE_DEF_SEL( layer,
						"layer" );

_APPKIT_PRIVATE_DEF_SEL( setOpaque_,
						"setOpaque:" );

_APPKIT_PRIVATE_DEF_SEL( setWantsLayer_,
						"setWantsLayer:" );

_APPKIT_PRIVATE_DEF_SEL( displayLinkWithTarget_selector_,
						"displayLinkWithTarget:selector:" );

_APPKIT_PRIVATE_DEF_SEL( setEventHandler_,
						"setEventHandler:" );

_APPKIT_PRIVATE_DEF_SEL( getUserData_,
						"getUserData" );

_APPKIT_PRIVATE_DEF_SEL( contentView,
						"contentView" );

_APPKIT_PRIVATE_DEF_SEL( setContentView_,
						"setContentView:" );

_APPKIT_PRIVATE_DEF_SEL( makeKeyAndOrderFront_,
						"makeKeyAndOrderFront:" );

_APPKIT_PRIVATE_DEF_SEL( setKeyEquivalentModifierMask_,
						"setKeyEquivalentModifierMask:" );

_APPKIT_PRIVATE_DEF_SEL(setBackgroundColor_,
						"setBackgroundColor:" );

_APPKIT_PRIVATE_DEF_SEL( setMainMenu_,
						"setMainMenu:" );

_APPKIT_PRIVATE_DEF_SEL( setSubmenu_,
						"setSubmenu:" );

_APPKIT_PRIVATE_DEF_SEL( setTitle_,
						"setTitle:" );

_APPKIT_PRIVATE_DEF_SEL( title_,
						"title" );

_APPKIT_PRIVATE_DEF_SEL( setFrameAutosaveName_,
						"setFrameAutosaveName:" );

_APPKIT_PRIVATE_DEF_SEL( setFrameUsingName_,
						"setFrameUsingName:" );

_APPKIT_PRIVATE_DEF_SEL(setFrame_display_,
						"setFrame:display:" );

_APPKIT_PRIVATE_DEF_SEL( setFrame_display_animate_,
						"setFrame:display:animate:" );

_APPKIT_PRIVATE_DEF_SEL( windows,
						"windows" );

_APPKIT_PRIVATE_DEF_SEL( openPanel_,
						"openPanel" );

_APPKIT_PRIVATE_DEF_SEL( beginSheetModalForWindow_completionHandler_,
						"beginSheetModalForWindow:completionHandler:" );

_APPKIT_PRIVATE_DEF_SEL( urls_,
						"URLs" );

// NSEvent selectors
_APPKIT_PRIVATE_DEF_SEL( type,
						"type" );

_APPKIT_PRIVATE_DEF_SEL( modifierFlags,
						"modifierFlags" );

_APPKIT_PRIVATE_DEF_SEL( window,
						"window" );

_APPKIT_PRIVATE_DEF_SEL( windowNumber,
						"windowNumber" );

_APPKIT_PRIVATE_DEF_SEL( timestamp,
						"timestamp" );

_APPKIT_PRIVATE_DEF_SEL( pressure,
						"pressure" );

_APPKIT_PRIVATE_DEF_SEL( clickCount,
						"clickCount" );

_APPKIT_PRIVATE_DEF_SEL( buttonNumber,
						"buttonNumber" );

_APPKIT_PRIVATE_DEF_SEL( eventNumber,
						"eventNumber" );

_APPKIT_PRIVATE_DEF_SEL( locationInWindow,
						"locationInWindow" );

_APPKIT_PRIVATE_DEF_SEL( deltaX,
						"deltaX" );

_APPKIT_PRIVATE_DEF_SEL( deltaY,
						"deltaY" );

_APPKIT_PRIVATE_DEF_SEL( deltaZ,
						"deltaZ" );

_APPKIT_PRIVATE_DEF_SEL( hasPreciseScrollingDeltas,
						"hasPreciseScrollingDeltas" );

_APPKIT_PRIVATE_DEF_SEL( scrollingDeltaX,
						"scrollingDeltaX" );

_APPKIT_PRIVATE_DEF_SEL( scrollingDeltaY,
						"scrollingDeltaY" );

_APPKIT_PRIVATE_DEF_SEL( momentumPhase,
						"momentumPhase" );

_APPKIT_PRIVATE_DEF_SEL( isDirectionInvertedFromDevice,
						"isDirectionInvertedFromDevice" );

_APPKIT_PRIVATE_DEF_SEL( characters,
						"characters" );

_APPKIT_PRIVATE_DEF_SEL( charactersIgnoringModifiers,
						"charactersIgnoringModifiers" );

_APPKIT_PRIVATE_DEF_SEL( charactersByApplyingModifiers_,
						"charactersByApplyingModifiers:" );

_APPKIT_PRIVATE_DEF_SEL( isARepeat,
						"isARepeat" );

_APPKIT_PRIVATE_DEF_SEL( keyCode,
						"keyCode" );

_APPKIT_PRIVATE_DEF_SEL( trackingNumber,
						"trackingNumber" );

_APPKIT_PRIVATE_DEF_SEL( userData,
						"userData" );

_APPKIT_PRIVATE_DEF_SEL( subtype,
						"subtype" );

_APPKIT_PRIVATE_DEF_SEL( data1,
						"data1" );

_APPKIT_PRIVATE_DEF_SEL( data2,
						"data2" );

_APPKIT_PRIVATE_DEF_SEL( magnification,
						"magnification" );

_APPKIT_PRIVATE_DEF_SEL( rotation,
						"rotation" );

_APPKIT_PRIVATE_DEF_SEL( deviceID,
						"deviceID" );

_APPKIT_PRIVATE_DEF_SEL( absoluteX,
						"absoluteX" );

_APPKIT_PRIVATE_DEF_SEL( absoluteY,
						"absoluteY" );

_APPKIT_PRIVATE_DEF_SEL( absoluteZ,
						"absoluteZ" );

_APPKIT_PRIVATE_DEF_SEL( buttonMask,
						"buttonMask" );

_APPKIT_PRIVATE_DEF_SEL( tilt,
						"tilt" );

_APPKIT_PRIVATE_DEF_SEL( tangentialPressure,
						"tangentialPressure" );

_APPKIT_PRIVATE_DEF_SEL( vendorID,
						"vendorID" );

_APPKIT_PRIVATE_DEF_SEL( tabletID,
						"tabletID" );

_APPKIT_PRIVATE_DEF_SEL( pointingDeviceID,
						"pointingDeviceID" );

_APPKIT_PRIVATE_DEF_SEL( systemTabletID,
						"systemTabletID" );

_APPKIT_PRIVATE_DEF_SEL( vendorPointingDeviceType,
						"vendorPointingDeviceType" );

_APPKIT_PRIVATE_DEF_SEL( pointingDeviceSerialNumber,
						"pointingDeviceSerialNumber" );

_APPKIT_PRIVATE_DEF_SEL( uniqueID,
						"uniqueID" );

_APPKIT_PRIVATE_DEF_SEL( capabilityMask,
						"capabilityMask" );

_APPKIT_PRIVATE_DEF_SEL( pointingDeviceType,
						"pointingDeviceType" );

_APPKIT_PRIVATE_DEF_SEL( isEnteringProximity,
						"isEnteringProximity" );

_APPKIT_PRIVATE_DEF_SEL( phase,
						"phase" );

_APPKIT_PRIVATE_DEF_SEL( stage,
						"stage" );

_APPKIT_PRIVATE_DEF_SEL( stageTransition,
						"stageTransition" );

_APPKIT_PRIVATE_DEF_SEL( associatedEventsMask,
						"associatedEventsMask" );

_APPKIT_PRIVATE_DEF_SEL( pressureBehavior,
						"pressureBehavior" );

_APPKIT_PRIVATE_DEF_SEL( mouseLocation,
						"mouseLocation" );

_APPKIT_PRIVATE_DEF_SEL( pressedMouseButtons,
						"pressedMouseButtons" );

_APPKIT_PRIVATE_DEF_SEL( doubleClickInterval,
						"doubleClickInterval" );

_APPKIT_PRIVATE_DEF_SEL( keyRepeatDelay,
						"keyRepeatDelay" );

_APPKIT_PRIVATE_DEF_SEL( keyRepeatInterval,
						"keyRepeatInterval" );

_APPKIT_PRIVATE_DEF_SEL( isMouseCoalescingEnabled,
						"isMouseCoalescingEnabled" );

_APPKIT_PRIVATE_DEF_SEL( setMouseCoalescingEnabled_,
						"setMouseCoalescingEnabled:" );

_APPKIT_PRIVATE_DEF_SEL( isSwipeTrackingFromScrollEventsEnabled,
						"isSwipeTrackingFromScrollEventsEnabled" );

_APPKIT_PRIVATE_DEF_SEL(otherEventWithType_location_modifierFlags_timestamp_windowNumber_context_subtype_data1_data2_,
						"otherEventWithType:location:modifierFlags:timestamp:windowNumber:context:subtype:data1:data2:");

_APPKIT_PRIVATE_DEF_SEL(currentRenderPassDescriptor,
						"currentRenderPassDescriptor");

_APPKIT_PRIVATE_DEF_SEL(convertPoint_fromView_,
						"convertPoint:fromView:");

// Screen
_APPKIT_PRIVATE_DEF_SEL(mainScreen, "mainScreen");

_APPKIT_PRIVATE_DEF_SEL(deepestScreen, "deepestScreen");

_APPKIT_PRIVATE_DEF_SEL(maximumFramesPerSecond, "maximumFramesPerSecond");

_APPKIT_PRIVATE_DEF_SEL(screen, "screen");

_APPKIT_PRIVATE_DEF_SEL(screens, "screens");

_APPKIT_PRIVATE_DEF_SEL(visibleFrame, "visibleFrame");

_APPKIT_PRIVATE_DEF_SEL(deviceDescription, "deviceDescription");

_APPKIT_PRIVATE_DEF_SEL(safeAreaInsets, "safeAreaInsets");

_APPKIT_PRIVATE_DEF_SEL(auxiliaryTopLeftArea, "auxiliaryTopLeftArea");

_APPKIT_PRIVATE_DEF_SEL(auxiliaryTopRightArea, "auxiliaryTopRightArea");

_APPKIT_PRIVATE_DEF_SEL(maximumExtendedDynamicRangeColorComponentValue,
						"maximumExtendedDynamicRangeColorComponentValue");

_APPKIT_PRIVATE_DEF_SEL(maximumPotentialExtendedDynamicRangeColorComponentValue,
						"maximumPotentialExtendedDynamicRangeColorComponentValue");

_APPKIT_PRIVATE_DEF_SEL(maximumReferenceExtendedDynamicRangeColorComponentValue,
						"maximumReferenceExtendedDynamicRangeColorComponentValue");

_APPKIT_PRIVATE_DEF_SEL(convertRectToBacking_, "convertRectToBacking:");

_APPKIT_PRIVATE_DEF_SEL(convertRectFromBacking_, "convertRectFromBacking:");

_APPKIT_PRIVATE_DEF_SEL(colorSpace, "colorSpace");

_APPKIT_PRIVATE_DEF_SEL(depth, "depth");

_APPKIT_PRIVATE_DEF_SEL(supportedWindowDepths, "supportedWindowDepths");

_APPKIT_PRIVATE_DEF_SEL(backingAlignedRect_options_, "backingAlignedRect:options:");

// ColorSpace
_APPKIT_PRIVATE_DEF_SEL(sRGBColorSpace, "sRGBColorSpace");

_APPKIT_PRIVATE_DEF_SEL(extendedSRGBColorSpace, "extendedSRGBColorSpace");

_APPKIT_PRIVATE_DEF_SEL(displayP3ColorSpace, "displayP3ColorSpace");

_APPKIT_PRIVATE_DEF_SEL(adobeRGB1998ColorSpace, "adobeRGB1998ColorSpace");

_APPKIT_PRIVATE_DEF_SEL(genericRGBColorSpace, "genericRGBColorSpace");

_APPKIT_PRIVATE_DEF_SEL(deviceRGBColorSpace, "deviceRGBColorSpace");

_APPKIT_PRIVATE_DEF_SEL(numberOfColorComponents, "numberOfColorComponents");

_APPKIT_PRIVATE_DEF_SEL(colorSpaceModel, "colorSpaceModel");

// Window
_APPKIT_PRIVATE_DEF_SEL(minSize, "minSize");

_APPKIT_PRIVATE_DEF_SEL(setMinSize_, "setMinSize:");

_APPKIT_PRIVATE_DEF_SEL(setContentViewController_, "setContentViewController:");

_APPKIT_PRIVATE_DEF_SEL(contentViewController, "contentViewController");

_APPKIT_PRIVATE_DEF_SEL(styleMask, "styleMask");

_APPKIT_PRIVATE_DEF_SEL(setStyleMask_, "setStyleMask:");

_APPKIT_PRIVATE_DEF_SEL(level, "level");

_APPKIT_PRIVATE_DEF_SEL(setLevel_, "setLevel:");

_APPKIT_PRIVATE_DEF_SEL(collectionBehavior, "collectionBehavior");

_APPKIT_PRIVATE_DEF_SEL(setCollectionBehavior_, "setCollectionBehavior:");

_APPKIT_PRIVATE_DEF_SEL(acceptsMouseMovedEvents, "acceptsMouseMovedEvents");

_APPKIT_PRIVATE_DEF_SEL(setAcceptsMouseMovedEvents_, "setAcceptsMouseMovedEvents:");

_APPKIT_PRIVATE_DEF_SEL(contentLayoutRect, "contentLayoutRect");

_APPKIT_PRIVATE_DEF_SEL(center, "center");

_APPKIT_PRIVATE_DEF_SEL(miniaturize_, "miniaturize:");

_APPKIT_PRIVATE_DEF_SEL(toggleFullScreen_, "toggleFullScreen:");

_APPKIT_PRIVATE_DEF_SEL(makeFirstResponder_, "makeFirstResponder:");

// WindowDelegate
_APPKIT_PRIVATE_DEF_SEL(windowDidResize_, "windowDidResize:");

_APPKIT_PRIVATE_DEF_SEL(windowDidMove_, "windowDidMove:");

_APPKIT_PRIVATE_DEF_SEL(windowDidBecomeKey_, "windowDidBecomeKey:");

_APPKIT_PRIVATE_DEF_SEL(windowDidResignKey_, "windowDidResignKey:");

_APPKIT_PRIVATE_DEF_SEL(windowDidMiniaturize_, "windowDidMiniaturize:");

_APPKIT_PRIVATE_DEF_SEL(windowDidDeminiaturize_, "windowDidDeminiaturize:");

_APPKIT_PRIVATE_DEF_SEL(windowDidEnterFullScreen_, "windowDidEnterFullScreen:");

_APPKIT_PRIVATE_DEF_SEL(windowDidExitFullScreen_, "windowDidExitFullScreen:");

_APPKIT_PRIVATE_DEF_SEL(windowWillClose_, "windowWillClose:");

_APPKIT_PRIVATE_DEF_SEL(windowShouldClose_, "windowShouldClose:");

// Cursor
_APPKIT_PRIVATE_DEF_SEL(currentCursor, "currentCursor");

_APPKIT_PRIVATE_DEF_SEL(arrowCursor, "arrowCursor");

_APPKIT_PRIVATE_DEF_SEL(hide, "hide");

_APPKIT_PRIVATE_DEF_SEL(unhide, "unhide");

_APPKIT_PRIVATE_DEF_SEL(setHiddenUntilMouseMoves_, "setHiddenUntilMouseMoves:");

_APPKIT_PRIVATE_DEF_SEL(set, "set");

_APPKIT_PRIVATE_DEF_SEL(push, "push");

_APPKIT_PRIVATE_DEF_SEL(pop, "pop");

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------