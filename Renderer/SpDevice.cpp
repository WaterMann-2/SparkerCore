#include "SpDevice.h"


VkPhysicalDevice SpDevice::SpPhysicalDevice::getVkDevice()
{
	return VkPhysicalDevice();
}

SpDevice::SpPhysicalDeviceInfo* SpDevice::SpPhysicalDevice::getPhysicalDeviceInfo(){
	return &deviceInfo;
}

void SpDevice::SpPhysicalDevice::CreatePhysicalDevice(VkInstance Instance, vector<const char*> RequestedExtensions, VkSurfaceKHR Surface) {
	instance = Instance;
	requiredExtensions = RequestedExtensions;
	surface = Surface;

	pickDevice();
}


void SpDevice::SpPhysicalDevice::pickDevice(){
	uint32_t deviceCount = 0;

	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	SpDebug::SpConsole::fatalExit(deviceCount == 0, "Failed to find GPU with Vulkan support!", SpDebug::SP_EXIT_FAILED_TO_FIND_VALID_PHYSICAL_DEIVCE);

	vector<VkPhysicalDevice> devices(deviceCount);
	vector<VkPhysicalDeviceProperties> deviceProperties(deviceCount);
	vector<VkPhysicalDeviceFeatures> deviceFeatures(deviceCount);

	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	if (devices.size() == 1) {
		SpPhysicalDeviceInfo info{};
		info.device = devices[0];
		SpDebug::SpConsole::fatalExit(isDeviceSuitable(info), "Only device isn't suitable!", SpDebug::SP_EXIT_FAILED_TO_FIND_VALID_PHYSICAL_DEIVCE);
		// No need to rate the device if only one exists
		SpDebug::SpConsole::consoleWrite(SpDebug::SP_MESSAGE_INFO, "Found 1 device: " + string(deviceProperties[0].deviceName));

		deviceInfo.device = devices[0];
		return;
		//Only need to go past this point if there are multiple devices
	}

	// TODO Rate devices.
	/*
	int topScore = 0;
	for (const VkPhysicalDevice& deivce : devices) {

	}*/


}
bool SpDevice::SpPhysicalDevice::isDeviceSuitable(SpPhysicalDeviceInfo& info){
	vkGetPhysicalDeviceProperties(info.device, &info.properties);
	vkGetPhysicalDeviceFeatures(info.device, &info.features);

	info.queueFamily = SpCommon::Memory::findQueueFamilies(info.device, surface);

	bool extensionsSupported = checkDeviceExtensions(info);
	bool swapchainAdqequate = info.swapchainSupportDetails.compatiable();
	bool queueFamilyAdequate = info.queueFamily.isComplete();

	return extensionsSupported && swapchainAdqequate && queueFamilyAdequate;
}

bool SpDevice::SpPhysicalDevice::checkDeviceExtensions(SpPhysicalDeviceInfo& info){
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(info.device, nullptr, &extensionCount, nullptr);

	vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(info.device, nullptr, &extensionCount, availableExtensions.data());

	set<string> requestedExtensions(requiredExtensions.begin(), requiredExtensions.end());

	for (const VkExtensionProperties& extension : availableExtensions) requestedExtensions.erase(extension.extensionName);

	info.extensionProperties = availableExtensions;

	info.extensionNames.resize(availableExtensions.size());
	int i = 0;
	for (const VkExtensionProperties& extension : info.extensionProperties) {
		info.extensionNames[i] = extension.extensionName;
	}

	return requestedExtensions.empty();
}

void SpDevice::SpPhysicalDevice::querySwapchainSupport(SpPhysicalDeviceInfo& info) {
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(info.device, surface, &info.swapchainSupportDetails.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(info.device, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		info.swapchainSupportDetails.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(info.device, surface, &formatCount, info.swapchainSupportDetails.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(info.device, surface, &presentModeCount, nullptr);

	if (formatCount != 0) {
		info.swapchainSupportDetails.formats.resize(presentModeCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(info.device, surface, &presentModeCount, info.swapchainSupportDetails.formats.data());
	}
}


SpDevice::SpLogicalDeviceInfo* SpDevice::SpLogicalDevice::getDeviceInfo(){
	return &deviceInfo;
}

void SpDevice::SpLogicalDevice::CreateLogicalDevice(VkInstance Instance, SpPhysicalDeviceInfo& PhysicalDevice, vector<const char*> enabledValidationLayerNames) {
	instance = Instance;
	pPhysicalDeviceInfo = &PhysicalDevice;

	createDevice(enabledValidationLayerNames);
}

void SpDevice::SpLogicalDevice::createDevice(vector<const char*> enabledValidationLayerNames){
	vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	set<uint32_t> uniqueQueueFamilies = { pPhysicalDeviceInfo->queueFamily.graphicsFamily.value(), pPhysicalDeviceInfo->queueFamily.presentFamily.value(), pPhysicalDeviceInfo->queueFamily.transferFamily.value()};

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &pPhysicalDeviceInfo->features;

	createInfo.enabledExtensionCount = static_cast<uint32_t>(pPhysicalDeviceInfo->extensionNames.size());
	createInfo.ppEnabledExtensionNames = pPhysicalDeviceInfo->extensionNames.data();

	createInfo.enabledLayerCount = static_cast<uint32_t>(enabledValidationLayerNames.size());
	createInfo.ppEnabledLayerNames = enabledValidationLayerNames.data();

	VkResult result = vkCreateDevice(pPhysicalDeviceInfo->device, &createInfo, nullptr, &deviceInfo.device);

	SpDebug::SpConsole::vkResultExitCheck(result, "Failed to create logical device!", "Created logical device", SpDebug::SP_EXIT_FAILED_TO_CREATE_LOGICAL_DEVICE);

	vkGetDeviceQueue(deviceInfo.device, pPhysicalDeviceInfo->queueFamily.graphicsFamily.value(), 0, &deviceInfo.graphicsQueue);
	vkGetDeviceQueue(deviceInfo.device, pPhysicalDeviceInfo->queueFamily.presentFamily.value(), 0, &deviceInfo.presentQueue);
	vkGetDeviceQueue(deviceInfo.device, pPhysicalDeviceInfo->queueFamily.transferFamily.value(), 0, &deviceInfo.transferQueue);
}
