// Module: tests/Smoke
// File: UmbrellaHeadersTest.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-02
// Notes: Compile-time smoke test: every umbrella header must parse together in a single
// translation unit. Successfully compiling and linking this file is the real
// assertion; the test body just gives CTest something to report.
//

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "MetalFX/MetalFX.hpp"
#include "MetalKit/MetalKit.hpp"
#include "QuartzCore/QuartzCore.hpp"
#include "AppKit/AppKit.hpp"

#include <gtest/gtest.h>

TEST(Smoke, UmbrellaHeadersCompile)
{
	SUCCEED();
}
