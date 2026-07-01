//
// Module: tests/Foundation
// File: StringTests.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-02
// Notes: Runtime checks for the Foundation string wrappers. Links against METAL_CPP,
// which provides the Objective-C bridging implementation; this TU only includes
// the public headers (it must NOT define the *_PRIVATE_IMPLEMENTATION macros).
//

#include "Foundation/Foundation.hpp"

#include <gtest/gtest.h>

TEST(FoundationString, RoundTripsUtf8)
{
	NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

	NS::String* pString = NS::String::string("hello", NS::UTF8StringEncoding);
	ASSERT_NE(pString, nullptr);
	EXPECT_EQ(pString->length(), 5u);
	EXPECT_STREQ(pString->utf8String(), "hello");

	pPool->release();
}
