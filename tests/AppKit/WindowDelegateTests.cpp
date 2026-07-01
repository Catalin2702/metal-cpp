//
// Module: tests/AppKit
// File: WindowDelegateTests.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-02
// Notes: Verifies that the NS::WindowDelegate base forwards through virtual overrides
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
