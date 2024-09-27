#include "Swapchain.h"

VkSwapchainKHR* Graphics::SVulkan::Swapchain::createSwapchain(VkDevice& srcDevice, VkPhysicalDevice& srcPhysicalDevice, SpWindow& window){
	device = &srcDevice;
	physicalDevice = &srcPhysicalDevice;
	surface = window.getWindowSurface();

	return &swapchain;
}