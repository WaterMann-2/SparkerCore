#pragma once

#include <vector>
#include <set>

#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Swapchain.h"

using std::vector;
using std::set;

bool enableValidationLayers = true;
vector<const char*> validationLayers{
	"VK_LAYER_KHRONOS_validation"
};

namespace Graphics {
	
	namespace SVulkan {


		namespace Begin {
			VkInstance createInstance();

			/// <summary>
			/// Picks first available valid device
			/// TODO Rate devices and pick the best one
			/// TODO User override on selected device
			/// </summary>
			/// <param name="instance">Current vulkan instance being used</param>
			/// <param name="validDevices">Optional field for getting the list of valid devices found with scores</param>
			/// <returns></returns>
			VkPhysicalDevice pickPhysicalDevice(VkInstance instance, vector<VkPhysicalDevice>* validDevices, vector<const char*> deviceExtensions);

		}

		namespace End {

		}

		

		namespace Utils {
			vector<const char*> Utils::getRequiredExtensions();
			int32_t ratePhysicalDevice(VkPhysicalDevice device, vector<const char*> deviceExtensions);
		}

		
	}

	namespace Debug {

		VkDebugUtilsMessengerEXT setupDebugMessenger(VkInstance instance);
		VkResult CreateDebugMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		VkDebugUtilsMessengerCreateInfoEXT populateMessengerCreateInfo();
	}
	
}