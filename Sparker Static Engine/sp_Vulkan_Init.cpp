#include "sp_Vulkan_Init.h"
/*
void _sp_Vulkan::startup::createInstance(VkInstance& instance) {
	if (EnableValidationLayers && !checkValidationLayerSupport()) {
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
	VkResultCheck(SP_FATAL, instanceResult, "Vulkan instance successfully created created", "Failed to create Vulkan instance", true, 100);
}

bool _sp_Vulkan::startup::checkValidationLayerSupport() {
	uint32_t layerCount;
	//Need to run this command to get the layer count before making "availableLayers" init size
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	DCout(SP_INFO, std::to_string(layerCount) + " Vulkan layers supported");
	std::vector<VkLayerProperties> availableLayers(layerCount);

	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers) {
		string layerRequested;
		bool layerFound = false;

		for (const VkLayerProperties& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
			layerRequested = layerProperties.layerName;
		}

		if (!layerFound) {
			DCout(SP_ERROR, layerRequested + " requested but not found!");
			return false;
		}
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



void _sp_Vulkan::startup::setupDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger) {
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = populateDebugMessenger();
	VkResult debugCreateResult = createDebugUtilsMessenger(instance, &debugCreateInfo, nullptr, &debugMessenger);

	VkResultCheck(SP_ERROR, debugCreateResult, "Created debug messenger", "Failed to create debug messenger!", false);
}

VkResult _sp_Vulkan::startup::createDebugUtilsMessenger(VkInstance instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void _sp_Vulkan::startup::createSurface(VkInstance& instance, GLFWwindow*& window, VkSurfaceKHR& surface){
	int vulkanSupported = glfwVulkanSupported();
	if (vulkanSupported == GLFW_FALSE) {
		DCout(SP_FATAL, "Vulkan not supported!");
		std::exit(100);
	}

	VkResult surfaceCreateResult = glfwCreateWindowSurface(instance, window, nullptr, &surface);

	VkResultCheck(SP_FATAL, surfaceCreateResult, "Surface successfully created", "Failed to create surface!", true, 100);
}

void _sp_Vulkan::startup::pickPhysicalDevice(VkInstance& instance, VkSurfaceKHR& surface){
	VkPhysicalDevice physicalDevice = NULL;
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	FatalExit(deviceCount == 0, "Failed to find GPU with Vulkan support!", 103);


	vector<VkPhysicalDevice> devices(deviceCount);
	vector<int32_t> deviceScores(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	int32_t bestScore = 0;
	VkPhysicalDevice bestDevice = NULL;

	for (int i = 0; i < deviceCount; i++) {
		deviceScores[i] = ratePhysicalDevices(devices[i], surface);

		if (deviceScores[i] > bestScore) {
			bestScore = deviceScores[i];
			bestDevice = devices[i];
		}
	}

	FatalExit(bestDevice == VK_NULL_HANDLE, "Failed to find a suitable GPU!", 104);

}

int32_t _sp_Vulkan::startup::ratePhysicalDevices(VkPhysicalDevice& device, VkSurfaceKHR& surface) {
	
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);


	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	set<string> requiredExtensions(requiredDeviceExtensions.begin(), requiredDeviceExtensions.end());

	for (const VkExtensionProperties& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	bool requiredExtensionsSupported = requiredExtensions.empty();

	bool swapchainAdequate = false;
	if (requiredExtensionsSupported) {
		SwapchainSupportDetails swapchainSupport = getDeviceSwapchainDetails(device, surface);
		swapchainAdequate = !swapchainSupport.formats.empty() && !swapchainSupport.presentModes.empty();
	}

	//If swapchain is not adequate OR unavailable
	if (swapchainAdequate) return INT32_MIN;

	return 0;
}

SwapchainSupportDetails _sp_Vulkan::startup::getDeviceSwapchainDetails(VkPhysicalDevice device, VkSurfaceKHR surface){
	SwapchainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	return details;
}

*/