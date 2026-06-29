//
// Module: metal-cpp tests
// File: tests/AppKit/InputDispatcherTests.cpp
//
// Verifies that the NS::ViewInputDispatcher base (a real, vtable-backed C++
// class) forwards through virtual overrides. No Objective-C objects are touched,
// so these run anywhere.
//

#include "AppKit/AppKit.hpp"

#include <gtest/gtest.h>

namespace
{
	struct CountingDispatcher : NS::ViewInputDispatcher
	{
		int mouseDowns = 0;
		int scrolls = 0;

		void DispatchMouseDown(NS::Event*) override { ++mouseDowns; }
		void DispatchScrollWheel(NS::Event*) override { ++scrolls; }
	};
}

TEST(AppKitViewInputDispatcher, VirtualOverridesAreInvoked)
{
	CountingDispatcher dispatcher;
	NS::ViewInputDispatcher& base = dispatcher;

	base.DispatchMouseDown(nullptr);
	base.DispatchMouseDown(nullptr);
	base.DispatchScrollWheel(nullptr);

	EXPECT_EQ(dispatcher.mouseDowns, 2);
	EXPECT_EQ(dispatcher.scrolls, 1);
}

TEST(AppKitViewInputDispatcher, DefaultHandlersAreNoops)
{
	NS::ViewInputDispatcher base;

	EXPECT_NO_THROW(base.DispatchMouseDown(nullptr));
	EXPECT_NO_THROW(base.DispatchKeyDown(nullptr));
	EXPECT_NO_THROW(base.DispatchScrollWheel(nullptr));
}
