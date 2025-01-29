#pragma once

#include <SpDebug.h>

#include "Window.h"
#include "SpDevice.h"

class SpSwapchain{
public:

	void createSwapchain(VkInstance instance);

	void recreate();
private:
	VkSwapchainKHR swapchain;
	int swapchainImagecount;

	vector<VkImage> swapchainImages;

	SpDevice::SpPhysicalDeviceInfo* physicalDeviceInfo;
	SpDevice::SpLogicalDeviceInfo* deviceInfo;

	SpWindow* window;

	VkSurfaceFormatKHR surfaceFormat;
	VkPresentModeKHR presentMode;
	VkExtent2D swapchainExtent;

	void chooseSurfaceFormat();
	void choosePresentMode();
	void chooseExtent();
};

