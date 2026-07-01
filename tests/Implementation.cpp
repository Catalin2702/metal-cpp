//
// Module: tests
// File: Implementation.cpp
// Created by: Catalin Chirosca
// Created: 2026-07-02
// Updated by: Catalin Chirosca
// Updated: 2026-07-02
// Notes: metal-cpp is header-only. This is the single translation unit that
// defines the private class/selector symbols for the test executables. It is
// the tests' equivalent of the implementation TU every consumer must provide
// (see the README). No other test source may define the *_PRIVATE_IMPLEMENTATION
// macros, otherwise the symbols would be emitted more than once.
//

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTLFX_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"
#include "MetalFX/MetalFX.hpp"
#include "MetalKit/MetalKit.hpp"
#include "QuartzCore/QuartzCore.hpp"
#include "AppKit/AppKit.hpp"
