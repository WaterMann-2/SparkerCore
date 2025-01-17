#include "Renderer.h"

void Renderer::CreateInstance(SpRendererInstanceCreateInfo SpCreateInfo) {

	getRequiredExtensions(SpCreateInfo.requestedExtensions, SpCreateInfo.debugEnabled);

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = SpCreateInfo.applicationName.c_str();
	appInfo.applicationVersion = SpCreateInfo.version;
	appInfo.pEngineName = "Sparker Engine";
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
	createInfo.ppEnabledExtensionNames = requiredExtensions.data();

	if (SpCreateInfo.debugEnabled = true) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(SpCreateInfo.requestedLayers.size());
		createInfo.ppEnabledLayerNames = SpCreateInfo.requestedLayers.data();

		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = Debug::SpConsole::PopulateDebugMessenger();

		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	} else {
		createInfo.enabledLayerCount = 0;
	}

	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

	Debug::SpConsole::vkResultExitCheck(result, "Failed to create Vulkan instance!", "Created Vulkan Instance", Debug::SP_EXIT_FAILED_TO_CREATE_INSTANCE);

	if (SpCreateInfo.debugEnabled) {
		createDebugMessenger();
	}
}

void Renderer::createDebugMessenger(){
	VkDebugUtilsMessengerCreateInfoEXT createInfo = Debug::SpConsole::PopulateDebugMessenger();

	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	VkResult debugCreateResult = VK_ERROR_EXTENSION_NOT_PRESENT;
	if (func != nullptr) {
		debugCreateResult = func(instance, &createInfo, nullptr, &debugMessenger);
	}

	Debug::SpConsole::vkResultCheck(Debug::SP_MESSAGE_FATAL, debugCreateResult, "Created Debug Messenger.", "Failed to create Debug Messenger!", Debug::SP_EXIT_FAILED_TO_CREATE_DEBUG_MESSENGER);
}

void Renderer::getRequiredExtensions(vector<const char*> RequestedExtensions, bool DebugModeOn){
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (DebugModeOn) extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
}
