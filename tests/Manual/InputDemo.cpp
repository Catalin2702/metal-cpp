//
// Module: metal-cpp tests
// File: tests/Manual/InputDemo.cpp
//
// Manual, interactive demo (NOT a CTest test): opens a real NSWindow with an
// MTKView, attaches an NS::ViewInputDispatcher and logs the mouse / keyboard /
// scroll events it receives to stdout. Build and run it by hand:
//
//   cmake --build <build> --target metal_cpp_input_demo
//   <build>/tests/metal_cpp_input_demo
//
// Move and click the mouse over the window and press some keys; close the window
// (or Cmd-Q) to quit.
//

#include "AppKit/AppKit.hpp"
#include "Metal/Metal.hpp"
#include "MetalKit/MetalKit.hpp"

#include <cstdio>

namespace
{
	// Logs every event forwarded by NS::View to its dispatcher.
	class InputLogger : public NS::ViewInputDispatcher
	{
		public:
			void DispatchMouseDown(NS::Event* pEvent) override { logMouse("mouseDown", pEvent); }
			void DispatchMouseUp(NS::Event* pEvent) override { logMouse("mouseUp", pEvent); }
			void DispatchMouseDragged(NS::Event* pEvent) override { logMouse("mouseDragged", pEvent); }
			void DispatchMouseMoved(NS::Event* pEvent) override { logMouse("mouseMoved", pEvent); }
			void DispatchRightMouseDown(NS::Event* pEvent) override { logMouse("rightMouseDown", pEvent); }
			void DispatchScrollWheel(NS::Event* pEvent) override
			{
				printf("[scrollWheel] deltaY=%.2f\n", pEvent->deltaY());
			}
			void DispatchKeyDown(NS::Event* pEvent) override { logKey("keyDown", pEvent); }
			void DispatchKeyUp(NS::Event* pEvent) override { logKey("keyUp", pEvent); }
			void DispatchFlagsChanged(NS::Event* pEvent) override
			{
				printf("[flagsChanged] keyCode=%u\n", pEvent->keyCode());
			}

		private:
			static void logMouse(const char* pName, NS::Event* pEvent)
			{
				const CGPoint location = pEvent->locationInWindow();
				printf("[%s] at (%.1f, %.1f)\n", pName, location.x, location.y);
			}

			static void logKey(const char* pName, NS::Event* pEvent)
			{
				NS::String* pChars = pEvent->characters();
				printf("[%s] keyCode=%u chars='%s'\n", pName, pEvent->keyCode(),
					   pChars ? pChars->utf8String() : "");
			}
	};

	// Builds the window once the app finished launching and owns the objects.
	class DemoAppDelegate : public NS::ApplicationDelegate
	{
		public:
			~DemoAppDelegate() override
			{
				if (_pView) _pView->release();
				if (_pWindow) _pWindow->release();
				if (_pDevice) _pDevice->release();
			}

			void applicationDidFinishLaunching(NS::Notification*) override
			{
				const CGRect frame = { { 120.0, 120.0 }, { 640.0, 480.0 } };

				_pDevice = MTL::CreateSystemDefaultDevice();

				_pWindow = NS::Window::alloc()->init(
					frame,
					NS::WindowStyleMaskTitled | NS::WindowStyleMaskClosable |
						NS::WindowStyleMaskMiniaturizable | NS::WindowStyleMaskResizable,
					NS::BackingStoreBuffered,
					false);

				// MTKView accepts first responder, so it also receives key events.
				_pView = MTK::View::alloc()->init(frame, _pDevice);
				_pView->setEventDispatcher(&_logger);

				// mouseMoved: is only delivered when the window opts in.
				_pWindow->setAcceptsMouseMovedEvents(true);

				_pWindow->setContentView(_pView);
				_pWindow->setTitle(NS::String::string("metal-cpp input demo", NS::UTF8StringEncoding));
				(void)_pWindow->makeFirstResponder(_pView);
				_pWindow->makeKeyAndOrderFront(nullptr);

				NS::Application::sharedApplication()->activateIgnoringOtherApps(true);

				printf("Window opened. Move/click the mouse, scroll and press keys.\n");
				printf("Close the window or press Cmd-Q to quit.\n");
			}

			bool applicationShouldTerminateAfterLastWindowClosed(NS::Application*) override { return true; }

		private:
			InputLogger  _logger;
			MTL::Device* _pDevice = nullptr;
			NS::Window*  _pWindow = nullptr;
			MTK::View*   _pView = nullptr;
	};
}

int main()
{
	NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

	DemoAppDelegate delegate;

	NS::Application* pApp = NS::Application::sharedApplication();
	pApp->setDelegate(&delegate);
	(void)pApp->setActivationPolicy(NS::ActivationPolicyRegular);
	pApp->run();

	pPool->release();
	return 0;
}
