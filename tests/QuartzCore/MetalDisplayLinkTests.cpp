//
// Module: metal-cpp tests
// File: tests/QuartzCore/MetalDisplayLinkTests.cpp
//
// Verifies that the CA::MetalDisplayLinkDelegate base forwards through its
// virtual override.
//

#include "QuartzCore/QuartzCore.hpp"

#include <gtest/gtest.h>

namespace
{
	struct RecordingDelegate : CA::MetalDisplayLinkDelegate
	{
		int updates = 0;

		void metalDisplayLinkNeedsUpdate(CA::MetalDisplayLink*, CA::MetalDisplayLinkUpdate*) override { ++updates; }
	};
}

TEST(QuartzCoreMetalDisplayLink, DelegateOverrideIsInvoked)
{
	RecordingDelegate delegate;
	CA::MetalDisplayLinkDelegate& base = delegate;

	base.metalDisplayLinkNeedsUpdate(nullptr, nullptr);

	EXPECT_EQ(delegate.updates, 1);
}
