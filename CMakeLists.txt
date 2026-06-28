#
# Module: metal-cpp
# File: CMakeLists.txt
# Created by: Catalin Chirosca
# Created: 2026-06-26
# Updated by: Catalin Chirosca
# Created: 2026-06-26
#

cmake_minimum_required(VERSION 3.21)

project(MetalCpp LANGUAGES CXX VERSION 27.0.1)

if(NOT APPLE)
	message(FATAL_ERROR
		"metal-cpp links against Apple frameworks (Metal, MetalKit, AppKit, "
		"Foundation, QuartzCore) and can only be built on Apple platforms."
	)
endif()

set(METAL_CPP_SUPPORTED_COMPILERS
	"AppleClang"
	"Clang"
)

if(NOT CMAKE_CXX_COMPILER_ID IN_LIST METAL_CPP_SUPPORTED_COMPILERS)
	message(FATAL_ERROR
		"metal-cpp only supports the LLVM Clang and Apple Clang compilers "
		"(CMAKE_CXX_COMPILER_ID 'AppleClang' or 'Clang'), but the current C++ "
		"compiler is '${CMAKE_CXX_COMPILER_ID}' "
		"(${CMAKE_CXX_COMPILER}). Reconfigure with an LLVM-based toolchain, "
		"e.g. -DCMAKE_CXX_COMPILER=clang++."
	)
endif()

set(CMAKE_CXX_STANDARD 17)

set(APPKIT_HEADERS
	AppKit/AppKit.hpp
	AppKit/AppKitPrivate.hpp
	AppKit/NSApplication.hpp
	AppKit/NSEvent.hpp
	AppKit/NSMenu.hpp
	AppKit/NSMenuItem.hpp
	AppKit/NSOpenPanel.hpp
	AppKit/NSRunningApplication.hpp
	AppKit/NSView.hpp
	AppKit/NSWindow.hpp
)

set(FOUNDATION_HEADERS
	Foundation/Foundation.hpp
	Foundation/NSArray.hpp
	Foundation/NSAutoreleasePool.hpp
	Foundation/NSBundle.hpp
	Foundation/NSData.hpp
	Foundation/NSDate.hpp
	Foundation/NSDefines.hpp
	Foundation/NSDictionary.hpp
	Foundation/NSEnumerator.hpp
	Foundation/NSError.hpp
	Foundation/NSLock.hpp
	Foundation/NSNotification.hpp
	Foundation/NSNumber.hpp
	Foundation/NSObjCRuntime.hpp
	Foundation/NSObject.hpp
	Foundation/NSPrivate.hpp
	Foundation/NSProcessInfo.hpp
	Foundation/NSRange.hpp
	Foundation/NSRunLoop.hpp
	Foundation/NSSet.hpp
	Foundation/NSSharedPtr.hpp
	Foundation/NSString.hpp
	Foundation/NSTypes.hpp
	Foundation/NSURL.hpp
)

set(METAL_HEADERS
	Metal/MTL4AccelerationStructure.hpp
	Metal/MTL4Archive.hpp
	Metal/MTL4ArgumentTable.hpp
	Metal/MTL4BinaryFunction.hpp
	Metal/MTL4BinaryFunctionDescriptor.hpp
	Metal/MTL4CommandAllocator.hpp
	Metal/MTL4CommandBuffer.hpp
	Metal/MTL4CommandEncoder.hpp
	Metal/MTL4CommandQueue.hpp
	Metal/MTL4CommitFeedback.hpp
	Metal/MTL4Compiler.hpp
	Metal/MTL4CompilerTask.hpp
	Metal/MTL4ComputeCommandEncoder.hpp
	Metal/MTL4ComputePipeline.hpp
	Metal/MTL4Counters.hpp
	Metal/MTL4FunctionDescriptor.hpp
	Metal/MTL4LibraryDescriptor.hpp
	Metal/MTL4LibraryFunctionDescriptor.hpp
	Metal/MTL4LinkingDescriptor.hpp
	Metal/MTL4MachineLearningCommandEncoder.hpp
	Metal/MTL4MachineLearningPipeline.hpp
	Metal/MTL4MeshRenderPipeline.hpp
	Metal/MTL4PipelineDataSetSerializer.hpp
	Metal/MTL4PipelineState.hpp
	Metal/MTL4RenderCommandEncoder.hpp
	Metal/MTL4RenderPass.hpp
	Metal/MTL4RenderPipeline.hpp
	Metal/MTL4SpecializedFunctionDescriptor.hpp
	Metal/MTL4StitchedFunctionDescriptor.hpp
	Metal/MTL4TileRenderPipeline.hpp
	Metal/MTLAccelerationStructure.hpp
	Metal/MTLAccelerationStructureCommandEncoder.hpp
	Metal/MTLAccelerationStructureTypes.hpp
	Metal/MTLAllocation.hpp
	Metal/MTLArgument.hpp
	Metal/MTLArgumentEncoder.hpp
	Metal/MTLBinaryArchive.hpp
	Metal/MTLBlitCommandEncoder.hpp
	Metal/MTLBlitPass.hpp
	Metal/MTLBuffer.hpp
	Metal/MTLCaptureManager.hpp
	Metal/MTLCaptureScope.hpp
	Metal/MTLCommandBuffer.hpp
	Metal/MTLCommandEncoder.hpp
	Metal/MTLCommandQueue.hpp
	Metal/MTLComputeCommandEncoder.hpp
	Metal/MTLComputePass.hpp
	Metal/MTLComputePipeline.hpp
	Metal/MTLCounters.hpp
	Metal/MTLDataType.hpp
	Metal/MTLDefines.hpp
	Metal/MTLDepthStencil.hpp
	Metal/MTLDevice.hpp
	Metal/MTLDrawable.hpp
	Metal/MTLDynamicLibrary.hpp
	Metal/MTLEvent.hpp
	Metal/MTLFence.hpp
	Metal/MTLFunctionConstantValues.hpp
	Metal/MTLFunctionDescriptor.hpp
	Metal/MTLFunctionHandle.hpp
	Metal/MTLFunctionLog.hpp
	Metal/MTLFunctionStitching.hpp
	Metal/MTLGPUAddress.hpp
	Metal/MTLHeaderBridge.hpp
	Metal/MTLHeap.hpp
	Metal/MTLIOCommandBuffer.hpp
	Metal/MTLIOCommandQueue.hpp
	Metal/MTLIOCompressor.hpp
	Metal/MTLIndirectCommandBuffer.hpp
	Metal/MTLIndirectCommandEncoder.hpp
	Metal/MTLIntersectionFunctionTable.hpp
	Metal/MTLLibrary.hpp
	Metal/MTLLinkedFunctions.hpp
	Metal/MTLLogState.hpp
	Metal/MTLParallelRenderCommandEncoder.hpp
	Metal/MTLPipeline.hpp
	Metal/MTLPixelFormat.hpp
	Metal/MTLPrivate.hpp
	Metal/MTLRasterizationRate.hpp
	Metal/MTLRenderCommandEncoder.hpp
	Metal/MTLRenderPass.hpp
	Metal/MTLRenderPipeline.hpp
	Metal/MTLResidencySet.hpp
	Metal/MTLResource.hpp
	Metal/MTLResourceStateCommandEncoder.hpp
	Metal/MTLResourceStatePass.hpp
	Metal/MTLResourceViewPool.hpp
	Metal/MTLSampler.hpp
	Metal/MTLStageInputOutputDescriptor.hpp
	Metal/MTLTensor.hpp
	Metal/MTLTexture.hpp
	Metal/MTLTextureViewPool.hpp
	Metal/MTLTypes.hpp
	Metal/MTLVersion.hpp
	Metal/MTLVertexDescriptor.hpp
	Metal/MTLVisibleFunctionTable.hpp
	Metal/Metal.hpp
)

set(METALFX_HEADERS
	MetalFX/MTL4FXFrameInterpolator.hpp
	MetalFX/MTL4FXSpatialScaler.hpp
	MetalFX/MTL4FXTemporalDenoisedScaler.hpp
	MetalFX/MTL4FXTemporalScaler.hpp
	MetalFX/MTLFXDefines.hpp
	MetalFX/MTLFXFrameInterpolator.hpp
	MetalFX/MTLFXPrivate.hpp
	MetalFX/MTLFXSpatialScaler.hpp
	MetalFX/MTLFXTemporalDenoisedScaler.hpp
	MetalFX/MTLFXTemporalScaler.hpp
	MetalFX/MetalFX.hpp
)

set(METALKIT_HEADERS
	MetalKit/MTKTextureLoader.hpp
	MetalKit/MTKView.hpp
	MetalKit/MetalKit.hpp
	MetalKit/MetalKitPrivate.hpp
)

set(QUARTZCORE_HEADERS
	QuartzCore/CADefines.hpp
	QuartzCore/CADisplayLink.hpp
	QuartzCore/CAMetalDrawable.hpp
	QuartzCore/CAMetalLayer.hpp
	QuartzCore/CAPrivate.hpp
	QuartzCore/QuartzCore.hpp
)

set(IMPLEMENTATION_SOURCES
	src/Implementation/Implementation.cpp
)

set(HEADERS
	${APPKIT_HEADERS}
	${FOUNDATION_HEADERS}
	${METAL_HEADERS}
	${METALFX_HEADERS}
	${METALKIT_HEADERS}
	${QUARTZCORE_HEADERS}
)

set(SOURCES
	${IMPLEMENTATION_SOURCES}
)

add_library(METAL_CPP
	${HEADERS}
	${SOURCES}
)

target_link_libraries(METAL_CPP
	"-framework Metal"
	"-framework MetalKit"
	"-framework AppKit"
	"-framework Foundation"
	"-framework QuartzCore"
)

target_include_directories(METAL_CPP PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
