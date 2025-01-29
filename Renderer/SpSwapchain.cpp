#include "SpSwapchain.h"

void SpSwapchain::createSwapchain(VkInstance instance){
	SwapchainSupportDetails& supportDetails = physicalDeviceInfo->swapchainSupportDetails;
	chooseSurfaceFormat();
	choosePresentMode();
	chooseExtent();

	uint32_t imageCount = supportDetails.capabilities.minImageCount + 1;

	if (supportDetails.capabilities.maxImageCount > 0 && imageCount > supportDetails.capabilities.maxImageCount) {
		imageCount = supportDetails.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = window->windowSurface();
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = swapchainExtent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //TODO Subject to change to transfer bit

	const int queueFamilycount = 3;

	uint32_t indices[queueFamilycount] = {
		physicalDeviceInfo->queueFamily.graphicsFamily.value(),
		physicalDeviceInfo->queueFamily.presentFamily.value(),
		physicalDeviceInfo->queueFamily.transferFamily.value()
	};

	createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	createInfo.queueFamilyIndexCount = static_cast<uint32_t>(queueFamilycount);
	createInfo.pQueueFamilyIndices = indices;

	createInfo.preTransform = supportDetails.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	VkResult result = vkCreateSwapchainKHR(deviceInfo->device, &createInfo, nullptr, &swapchain);

	SpDebug::SpConsole::vkResultExitCheck(result, "Failed to create swapchain!", "Created swapchain", SpDebug::SP_EXIT_FAILED_TO_CREATE_SWAPCHAIN);

	vkGetSwapchainImagesKHR(deviceInfo->device, swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(deviceInfo->device, swapchain, &imageCount, swapchainImages.data());
}

void SpSwapchain::chooseSurfaceFormat(){
	for (const VkSurfaceFormatKHR& format : physicalDeviceInfo->swapchainSupportDetails.formats) {
		if (format.format == VK_FORMAT_B8G8R8A8_UNORM && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			surfaceFormat = format;
			return;
		}
	}


	SpDebug::SpConsole::fatalExit("Failed to find Swapchain surface format!", SpDebug::SP_EXIT_FAILED_TO_FIND_SURFACE_FORMAT);
}

void SpSwapchain::choosePresentMode(){
	for (const VkPresentModeKHR& present : physicalDeviceInfo->swapchainSupportDetails.presentModes) {
		if (present == VK_PRESENT_MODE_MAILBOX_KHR) {
			presentMode = present;
			return;
		}
	}

	presentMode = VK_PRESENT_MODE_FIFO_KHR;
	//SpDebug::SpConsole::fatalExit("Failed to find swapchain present mode", SpDebug::SP_EXIT_FAILED_TO_FIND_PRESENT_MODE);
}

void SpSwapchain::chooseExtent(){
	VkSurfaceCapabilitiesKHR& capabilities = physicalDeviceInfo->swapchainSupportDetails.capabilities;
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		swapchainExtent = capabilities.currentExtent;
		return;
	} else {
		int width, height;
		glfwGetFramebufferSize(window->glWindow(), &width, &height);

		VkExtent2D extent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.minImageExtent.width);
		extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.minImageExtent.height);
	}
}
