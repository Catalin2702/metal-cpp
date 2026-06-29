//
// Module: metal-cpp tests
// File: tests/Smoke/UmbrellaHeadersTest.cpp
//
// Compile-time smoke test: every umbrella header must parse together in a single
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
