// Module: tests/QuartzCore
// File: MetalDisplayLinkTests.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-03
// Notes: Verifies that the CA::I_MetalDisplayLinkDelegate base forwards through its virtual override.
//

#include "QuartzCore/QuartzCore.hpp"

#include <gtest/gtest.h>

namespace
{
	struct RecordingDelegate : CA::I_MetalDisplayLinkDelegate
	{
		int updates = 0;

		void metalDisplayLinkNeedsUpdate(CA::MetalDisplayLink*, CA::MetalDisplayLinkUpdate*) override { ++updates; }
	};
}

TEST(QuartzCoreMetalDisplayLink, DelegateOverrideIsInvoked)
{
	RecordingDelegate delegate;
	CA::I_MetalDisplayLinkDelegate& base = delegate;

	base.metalDisplayLinkNeedsUpdate(nullptr, nullptr);

	EXPECT_EQ(delegate.updates, 1);
}
