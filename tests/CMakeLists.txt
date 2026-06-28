#
# Module: metal-cpp tests
# File: tests/CMakeLists.txt
#
# Only configured when METALCPP_BUILD_TESTS is ON (see the root CMakeLists.txt),
# which defaults to OFF when metal-cpp is consumed as a subdirectory / submodule.
# GoogleTest is fetched on demand so it is never downloaded for consumers.
#

include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

add_executable(metal_cpp_tests
	Foundation/StringTests.cpp
	Metal/DeviceTests.cpp
	AppKit/InputDispatcherTests.cpp
	AppKit/WindowDelegateTests.cpp
	QuartzCore/MetalDisplayLinkTests.cpp
	Smoke/UmbrellaHeadersTest.cpp
)

target_link_libraries(metal_cpp_tests PRIVATE
	METAL_CPP
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(metal_cpp_tests)

# Manual, interactive demo. Excluded from the default build (and from CTest)
# because it opens a real window and runs an AppKit event loop. Build on demand:
#   cmake --build <build> --target metal_cpp_input_demo
add_executable(metal_cpp_input_demo EXCLUDE_FROM_ALL
	Manual/InputDemo.cpp
)

target_link_libraries(metal_cpp_input_demo PRIVATE
	METAL_CPP
)
