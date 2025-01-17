#pragma once

#include <vector>

#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Window.h"

using std::vector;

namespace Graphics {
	namespace SVulkan {
		struct SwapchainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			vector<VkSurfaceFormatKHR> formats;
			vector <VkPresentModeKHR> presentModes;
		};

		class Swapchain {
		public:

			VkSwapchainKHR* createSwapchain(VkDevice& srcDevice, VkPhysicalDevice& srcPhysicalDevice, SpWindow& window);
	
			void recreateSwapchain();
	
			static SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice mPhysDevice);

		private:
			VkDevice* device;
			VkPhysicalDevice* physicalDevice;
			VkSurfaceKHR* surface;
			GLFWwindow* window;

			SwapchainSupportDetails pSwapSupport;
			VkSurfaceFormatKHR pSurfaceFormat;
			VkPresentModeKHR pPresentMode;
			VkExtent2D pExtent2D;

			VkSwapchainKHR swapchain;
			vector<VkImage> swapchainImages;

		private:
			
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats);
			VkPresentModeKHR chooseSwapPresentMode(const vector <VkPresentModeKHR>& avilableFormats);

		};
	}
}