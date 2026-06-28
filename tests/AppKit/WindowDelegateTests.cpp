//
// Module: metal-cpp tests
// File: tests/AppKit/WindowDelegateTests.cpp
//
// Verifies that the NS::WindowDelegate base forwards through virtual overrides
// and that its defaults behave as documented.
//

#include "AppKit/AppKit.hpp"

#include <gtest/gtest.h>

namespace
{
	struct RecordingWindowDelegate : NS::WindowDelegate
	{
		bool resized = false;

		void windowDidResize(NS::Notification*) override { resized = true; }
		bool windowShouldClose(NS::Window*) override { return false; }
	};
}

TEST(AppKitWindowDelegate, VirtualOverridesAreInvoked)
{
	RecordingWindowDelegate delegate;
	NS::WindowDelegate& base = delegate;

	base.windowDidResize(nullptr);

	EXPECT_TRUE(delegate.resized);
	EXPECT_FALSE(base.windowShouldClose(nullptr));
}

TEST(AppKitWindowDelegate, DefaultShouldCloseIsTrue)
{
	NS::WindowDelegate base;

	EXPECT_TRUE(base.windowShouldClose(nullptr));
	EXPECT_NO_THROW(base.windowWillClose(nullptr));
}
