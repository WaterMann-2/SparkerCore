#include "sp_Vulkan_Init.h"

VkInstance _sp_Vulkan::startup::createInstance(VkInstance& instance) {
	if (EnableValidationLayers && checkValidationLayerSupport()) {
		DCout(SP_ERROR, "Validation layers requested but not available!");
	}

	// TODO Read app info from file
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Sparker Engine";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Sparker Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	vector<const char*> requiredExtensions = getExtensions();

	VkInstanceCreateInfo instanceInfo{};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
	instanceInfo.ppEnabledExtensionNames = requiredExtensions.data();

	//When validation layers are enabled
	if (EnableValidationLayers) {
		VkDebugUtilsMessengerCreateInfoEXT debugInfo = populateDebugMessenger();

		instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		instanceInfo.ppEnabledLayerNames = validationLayers.data();
		instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugInfo;
	} else {
		instanceInfo.enabledLayerCount = 0;
		instanceInfo.pNext = nullptr;
	}

	VkResult instanceResult = vkCreateInstance(&instanceInfo, nullptr, &instance);
	VkResultCheck(SP_FATAL, instanceResult, "Vulkan instance successfully created created", "Failed to create Vulkan instance", true);

}

bool _sp_Vulkan::startup::checkValidationLayerSupport() {
	uint32_t layerCount;
	//Need to run this command to get the layer count before making "availableLayers" init size
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	DCout(SP_INFO, std::to_string(layerCount) + " Vulkan layers supported");
	std::vector<VkLayerProperties> availableLayers(layerCount);

	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const VkLayerProperties& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) return false;
	}

	return true;
}

vector<const char*> _sp_Vulkan::startup::getExtensions(){

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (EnableValidationLayers) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	DCout(SP_INFO, "Required extension count: " + std::to_string(extensions.size()));
	

	return extensions;
}

VkDebugUtilsMessengerCreateInfoEXT _sp_Vulkan::startup::populateDebugMessenger() {
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	debugCreateInfo = {};
	debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	debugCreateInfo.messageSeverity = SP_VK_VERBOSE | SP_VK_WARNING | SP_VK_ERROR;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	debugCreateInfo.pfnUserCallback = sp_Debug::VkDebugCallback;
	debugCreateInfo.pUserData = nullptr;
		
	return debugCreateInfo;
}