#pragma once

#include <SpDebug.h>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;
	std::optional<uint32_t> transferFamily;


	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
	}

};

namespace SpCommon {
	namespace Memory {

		static uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	}
}
