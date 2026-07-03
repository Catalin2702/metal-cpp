//
// Module: tests/AppKit
// File: InputDispatcherTests.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-04
// Notes: Verifies that the NS::ViewInputDispatcher base (a real, vtable-backed C++ class)
// forwards through virtual overrides. No Objective-C objects are touched,
// so these run anywhere.
//

#include "AppKit/AppKit.hpp"

#include <gtest/gtest.h>

namespace
{
	struct CountingDispatcher : NS::I_ViewEventDispatcher
	{
		int mouseDowns = 0;
		int scrolls = 0;
		int movedToWindow = 0;
		int laidOut = 0;

		void DispatchMouseDown(NS::Event*) override { ++mouseDowns; }
		void DispatchScrollWheel(NS::Event*) override { ++scrolls; }
		void DispatchViewDidMoveToWindow() override { ++movedToWindow; }
		void DispatchViewDidLayout() override { ++laidOut; }
	};
}

TEST(AppKitViewInputDispatcher, VirtualOverridesAreInvoked)
{
	CountingDispatcher dispatcher;
	NS::I_ViewEventDispatcher& base = dispatcher;

	base.DispatchMouseDown(nullptr);
	base.DispatchMouseDown(nullptr);
	base.DispatchScrollWheel(nullptr);

	EXPECT_EQ(dispatcher.mouseDowns, 2);
	EXPECT_EQ(dispatcher.scrolls, 1);
}

TEST(AppKitViewInputDispatcher, LifecycleOverridesAreInvoked)
{
	CountingDispatcher dispatcher;
	NS::I_ViewEventDispatcher& base = dispatcher;

	base.DispatchViewDidMoveToWindow();
	base.DispatchViewDidLayout();
	base.DispatchViewDidLayout();

	EXPECT_EQ(dispatcher.movedToWindow, 1);
	EXPECT_EQ(dispatcher.laidOut, 2);
}

TEST(AppKitViewInputDispatcher, DefaultHandlersAreNoops)
{
	NS::I_ViewEventDispatcher base;

	EXPECT_NO_THROW(base.DispatchMouseDown(nullptr));
	EXPECT_NO_THROW(base.DispatchKeyDown(nullptr));
	EXPECT_NO_THROW(base.DispatchScrollWheel(nullptr));
	EXPECT_NO_THROW(base.DispatchViewDidMoveToWindow());
	EXPECT_NO_THROW(base.DispatchViewDidEndLiveResize());
}
