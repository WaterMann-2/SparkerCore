#pragma once

#include <iostream>
#include <optional>
#include <set>

using std::optional;
using std::uint32_t;
using std::vector;
using std::set;

struct QueueFamilyIndices {
	optional<uint32_t> graphicsFamily;
	optional<uint32_t> presentFamily;


	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	vector<VkSurfaceFormatKHR> formats;
	vector <VkPresentModeKHR> presentModes;
};