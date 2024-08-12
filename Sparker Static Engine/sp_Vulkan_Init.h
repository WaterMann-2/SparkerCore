#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>

//#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>

#include "sp_Debug.h"
#include "sp_VkStructs.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>

#include "sp_Window.h"
#include "sp_Utility.h"
#include "sp_Primitive.h"

#include <vulkan/vulkan.h>


using std::uint32_t;
using std::string;
using std::vector;
using std::to_string;

const bool EnableValidationLayers = true;

const vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const vector<const char*> requiredDeviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAME_BUFFER_SIZE = 2;

namespace _sp_Vulkan {
	/*
	class startup {

	public:

		static void createInstance(VkInstance& instance);
		static void setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);
		static void createSurface(VkInstance& instance, GLFWwindow*& window, VkSurfaceKHR& surface);
		static void pickPhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface);

	private:

		static bool checkValidationLayerSupport();

		static vector<const char*> getExtensions();

		static VkDebugUtilsMessengerCreateInfoEXT populateDebugMessenger();
		static VkResult createDebugUtilsMessenger(VkInstance instance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

		static int32_t ratePhysicalDevices(VkPhysicalDevice& device, VkSurfaceKHR& surface);
		static SwapchainSupportDetails getDeviceSwapchainDetails(VkPhysicalDevice device, VkSurfaceKHR surface);

	};

	*/
}