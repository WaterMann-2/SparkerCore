#include "Window.h"

namespace Graphics {
	namespace SVulkan {

		void SpWindow::CreateWindow(const char* windowName,  int inWidth, int inHeight){
			
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			name = windowName;
			width = inWidth;
			height = inHeight;

			window = glfwCreateWindow(width, height, name, NULL, NULL);
			glfwMakeContextCurrent(window);
			glfwSetWindowUserPointer(window, this);
			glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
			
		}

		VkSurfaceKHR* SpWindow::createSurface(VkInstance instance){
			int vkSupported = glfwVulkanSupported();
			if (vkSupported == GLFW_FALSE) {
				Debug::Console::exitWithMsg("GLFW is NOT supporting Vulkan!", SP_EXIT_FAILED_TO_CREATE_INSTANCE);
			}
			Debug::Console::consoleWrite(SP_MESSAGE_INFO, "GLFW supports vulkan");

			Debug::Console::checkResult(SP_MESSAGE_INFO,
				glfwCreateWindowSurface(instance, window, nullptr, &windowSurface),
				"Created window surface", "Failed to create window surface", SP_EXIT_FAILED_TO_CREATE_WINDOW_SURFACE);

			return &windowSurface;
		}

		VkSurfaceKHR* SpWindow::getWindowSurface(){
			return &windowSurface;
		}

		int SpWindow::getWidth() { return width; }

		int SpWindow::getHeight() { return height; }

		void SpWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height){
			SpWindow* cWindow = reinterpret_cast<SpWindow*>(glfwGetWindowUserPointer(window));
			
			cWindow->framebufferResized = true;

			cWindow->width = width;
			cWindow->height = height;
		}

	}
}