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

bool EnableValidationLayers = true;

const vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

const vector<const char*> requiredDeviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAME_BUFFER_SIZE = 2;

namespace _sp_Vulkan {

	class startup {

	public:

		static VkInstance createInstance(VkInstance& instance);

	private:

		static bool checkValidationLayerSupport();

		static vector<const char*> getExtensions();

		static VkDebugUtilsMessengerCreateInfoEXT populateDebugMessenger();
	};


}