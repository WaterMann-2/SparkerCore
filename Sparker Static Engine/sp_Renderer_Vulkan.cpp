#include "sp_Renderer_Vulkan.h"

void Sparker_Engine::Renderer::sp_Vulkan2::CreateInstance(VkInstance& instance, VkApplicationInfo* appInfo, VkInstanceCreateInfo* createInfo){


	vector<const char*> requestedExtensions = getRequiredextensions();

	bool layerSupport = checkValidationLayerSupport(RequestedLayers);
	if (VALIDATION_LAYERS_ENABLED && !layerSupport) {
		SpConsole::fatalExit("Valudation layers requested but not available!", Sp_Exit_ValidationLayersUnavailable);
	}

	VkApplicationInfo AppInfo{};
	if (appInfo == nullptr) {
		SpConsole::consoleWrite(SP_MESSAGE_WARNING, "Application info not provided for VkInstance creation! Using default instead.");
		AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		AppInfo.pApplicationName = "Vulkan Application";
		AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		AppInfo.pEngineName = "Vulkan Engine";
		AppInfo.apiVersion = VK_API_VERSION_1_0;
	}
	else {
		AppInfo = *appInfo;
	}

	VkInstanceCreateInfo CreateInfo{};
	if (createInfo == nullptr) {
		SpConsole::consoleWrite(SP_MESSAGE_WARNING, "Instance create info not provided for VkInstance creation! Using default instead.");
		CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		CreateInfo.pApplicationInfo = &AppInfo;
		CreateInfo.enabledExtensionCount = static_cast<uint32_t>(requestedExtensions.size());
		CreateInfo.ppEnabledExtensionNames = requestedExtensions.data();

		if (VALIDATION_LAYERS_ENABLED) {
			CreateInfo.enabledLayerCount = static_cast<uint32_t>(RequestedLayers.size());
			CreateInfo.ppEnabledLayerNames = RequestedLayers.data();

			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = populateDebugMessenger();

			CreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;

		}
		else {
			CreateInfo.enabledLayerCount = 0;
			CreateInfo.pNext = nullptr;
		}

	}
	else {
		CreateInfo = *createInfo;
	}


	VkResult result = vkCreateInstance(&CreateInfo, nullptr, &instance);

	SpConsole::vkResultCheck(SP_MESSAGE_FATAL, result, "Created Vulkan instance.", "Failed to create vulkan instance!", SP_EXIT_FAILED_TO_CREATE_INSTANCE);
}

void Sparker_Engine::Renderer::sp_Vulkan2::SetupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT& debugMesenger){

	debugMesenger = {};
	
	VkDebugUtilsMessengerCreateInfoEXT createInfo = populateDebugMessenger();
	VkResult debugCreateResult = VK_ERROR_EXTENSION_NOT_PRESENT;

	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr) {
		debugCreateResult = func(instance, &createInfo, nullptr, &debugMesenger);
	}

	SpConsole::vkResultCheck(SP_MESSAGE_FATAL, debugCreateResult, "Created Debug Messenger.", "Failed to create Debug Messenger!", SP_EXIT_FAILED_TO_CREATE_DEBUG_MESSENGER);
}

void Sparker_Engine::Renderer::sp_Vulkan2::CreateSurface(VkInstance& instance, VkSurfaceKHR& surface, SpWindow& window){

	VkResult surfaceCreateResult = glfwCreateWindowSurface(instance, window, nullptr, &surface);

	SpConsole::vkResultExitCheck(surfaceCreateResult, "Failed to create Window Surface!", "Created Window Surface.", SP_EXIT_FAILED_TO_CREATE_WINDOW_SURFACE);
}

//Tools
inline bool Sparker_Engine::Renderer::sp_Vulkan2::checkValidationLayerSupport(vector<const char*> requestedLayers){

	
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	SpConsole::consoleWrite(SP_MESSAGE_INFO, std::to_string(layerCount) + " VK extensions supported");

	for (const char* layerName : requestedLayers) {
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

inline vector<const char*> Sparker_Engine::Renderer::sp_Vulkan2::getRequiredextensions() {
	
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (VALIDATION_LAYERS_ENABLED) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}

inline VkDebugUtilsMessengerCreateInfoEXT Sparker_Engine::Renderer::sp_Vulkan2::populateDebugMessenger() {
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	debugCreateInfo.messageSeverity = SP_VK_VERBOSE | SP_VK_WARNING | SP_VK_ERROR;
	debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	debugCreateInfo.pfnUserCallback = SpDebug::VkDebugCallback;
	debugCreateInfo.pUserData = nullptr;
	return debugCreateInfo;
}