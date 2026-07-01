//
// Module: tests/Metal
// File: DeviceTests.cpp
// Created by: Catalin Chirosca
// Created: 2026-06-29
// Updated by: Catalin Chirosca
// Updated: 2026-07-02
// Notes: Runtime check for Metal device creation. Skipped gracefully on machines
// without a Metal device (e.g. headless CI).
//

#include "Foundation/Foundation.hpp"
#include "Metal/Metal.hpp"

#include <gtest/gtest.h>

TEST(MetalDevice, CreatesSystemDefaultDevice)
{
	NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

	MTL::Device* pDevice = MTL::CreateSystemDefaultDevice();
	if (!pDevice)
	{
		pPool->release();
		GTEST_SKIP() << "No Metal device available on this machine.";
	}

	EXPECT_NE(pDevice->name(), nullptr);

	pDevice->release();
	pPool->release();
}
