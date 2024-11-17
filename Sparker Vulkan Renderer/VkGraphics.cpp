#include "VkGraphics.h"

namespace Graphics {
	namespace SVulkan {

		VkInstance Begin::createInstance() {
			VkInstance instance;

			VkApplicationInfo appInfo{};
			appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			appInfo.pApplicationName = "Sparker Engine";
			appInfo.pEngineName = "Sparker Engine";
			appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			appInfo.apiVersion = VK_API_VERSION_1_0;

			vector<const char*> extensions = Utils::getRequiredExtensions();

			VkInstanceCreateInfo instanceCreateInfo{};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &appInfo;
			instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

			if (enableValidationLayers) {
				instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
				instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();

				VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
				debugCreateInfo = Debug::populateMessengerCreateInfo();
				instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
			}
			else {
				instanceCreateInfo.enabledLayerCount = 0;
				instanceCreateInfo.ppEnabledLayerNames = nullptr;
			}

			VkResult instanceCreateInfo = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);


		}

		VkPhysicalDevice Begin::pickPhysicalDevice(VkInstance instance, vector<VkPhysicalDevice>* validDevices, vector<const char*> deviceExtensions){
			VkPhysicalDevice physicalDevice = NULL;
			uint32_t deviceCount = 0;
			vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

			if (deviceCount == 0) Debug::Console::exitWithMsg("Failed to find GPU with Vulkan support!", SP_EXIT_NO_VALID_GPU);

			if (validDevices != nullptr) { validDevices->resize(deviceCount); }

			vector<VkPhysicalDevice> physicalDevices(deviceCount);

			vkEnumeratePhysicalDevices(instance, deviceCount&, physicalDevices.data());
			
			if (deviceCount == 1) {
				int32_t deviceScore = Utils::ratePhysicalDevice(physicalDevices[1], deviceExtensions);
				if (deviceScore != INT32_MIN) return physicalDevices[1];
			}
			for (const VkPhysicalDevice device : physicalDevices) {

			}


			return VkPhysicalDevice();
		}
		
		vector<const char*> Utils::getRequiredExtensions() {
			uint32_t extensionCount = 0;
			const char** glfwExtensions;

			glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);

			vector<const char*> extensions(glfwExtensions, glfwExtensions + extensionCount);

			if (enableValidationLayers) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

			return extensions;
		}
		
		int32_t Utils::ratePhysicalDevice(VkPhysicalDevice device, vector<const char*> deviceExtensions) {
			VkPhysicalDeviceProperties deviceProperties;
			VkPhysicalDeviceFeatures deviceFeatures;
			bool extensionsSupported;

			//Extension support check
			{ 
				uint32_t extensionCount;
				vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

				vector<VkExtensionProperties> availableExtensions(extensionCount);
				vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

				set<string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

				for (const VkExtensionProperties extension : availableExtensions) {
					requiredExtensions.erase(extension.extensionName);
				}

				extensionsSupported = requiredExtensions.empty();
			} // End extension support check

			if (!extensionsSupported) return INT32_MIN;

			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

			bool swapchainAdequate = false;
			
			SwapchainSupportDetails swapchainSupport = Swapchain::querySwapchainSupport(device);

			swapchainAdequate = !swapchainSupport.formats.empty() && !swapchainSupport.presentModes.empty();

			return 0;
		}

	} //namespace SVulkan

	#pragma region Debug
	VkDebugUtilsMessengerEXT Debug::setupDebugMessenger(VkInstance instance) {

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = populateMessengerCreateInfo();
		VkDebugUtilsMessengerEXT debugMessenger;

		VkResult debugCreateResult = CreateDebugMessengerEXT(instance, &debugCreateInfo, nullptr, &debugMessenger);

		Graphics::Debug::Console::checkResult(SP_MESSAGE_ERROR, debugCreateResult, "Created Vulkan debug messenger", "Failed to create Vulkan debug messenger!");
		

		return debugMessenger;
	}

	VkResult Debug::CreateDebugMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {

		PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
		}

		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	VkDebugUtilsMessengerCreateInfoEXT Debug::populateMessengerCreateInfo() {
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity =
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

		debugCreateInfo.messageType =
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

		debugCreateInfo.pfnUserCallback = Graphics::Debug::Console::VulkanDebugCallback;
		debugCreateInfo.pUserData = nullptr;

		return debugCreateInfo;
	}
	#pragma endregion 
	//end region Debug
}

