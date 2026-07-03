//
// Module: tests/AppKit
// File: WindowDelegateTests.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-03
// Notes: Verifies that the NS::WindowDelegate base forwards through virtual overrides
// and that its defaults behave as documented.
//

#include "AppKit/AppKit.hpp"

#include <gtest/gtest.h>

namespace
{
	struct RecordingWindowDelegate : NS::I_WindowEventDispatcher
	{
		bool resized = false;

		void DispatchWindowDidResize(NS::Notification*) override { resized = true; }
		bool WindowShouldClose(NS::Window*) override { return false; }
	};
}

TEST(AppKitWindowDelegate, VirtualOverridesAreInvoked)
{
	RecordingWindowDelegate delegate;
	NS::I_WindowEventDispatcher& base = delegate;

	base.DispatchWindowDidResize(nullptr);

	EXPECT_TRUE(delegate.resized);
	EXPECT_FALSE(base.WindowShouldClose(nullptr));
}

TEST(AppKitWindowDelegate, DefaultShouldCloseIsTrue)
{
	NS::I_WindowEventDispatcher base;

	EXPECT_TRUE(base.WindowShouldClose(nullptr));
	EXPECT_NO_THROW(base.DispatchWindowWillClose(nullptr));
}
