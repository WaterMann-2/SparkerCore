#pragma once

#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Debug.h"

using std::vector;

namespace Graphics {
	namespace SVulkan {

		class SpWindow {
		public:
			bool framebufferResized = false;

			int getWidth();
			int getHeight();


			void CreateWindow(const char* windowName, int inWidth, int inHeight);
			VkSurfaceKHR* createSurface(VkInstance instance);

			VkSurfaceKHR* getWindowSurface();

		private:
			const char* name;
			GLFWwindow* window;
			VkSurfaceKHR windowSurface;


			int width = 0;
			int height = 0;

		private:
			static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		};
	}
}