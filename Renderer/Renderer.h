#pragma once

#define SPARKER_VULKAN_API
#include <Debug.h>

#include "Window.h"

struct SpRendererInstanceCreateInfo {
	string applicationName;
	uint32_t version;
	bool debugEnabled = true;
	vector<const char*> requestedExtensions;
	/// <summary>
	/// Doesn't currently work, only uses required extensions
	/// </summary>
	vector<const char*> requestedLayers;
};

class Renderer{
public:

	void CreateInstance(SpRendererInstanceCreateInfo createInfo);

private:

	VkDebugUtilsMessengerEXT debugMessenger;

	VkInstance instance;

	vector<const char*> requiredExtensions;

private:

	void createDebugMessenger();

	void getRequiredExtensions(vector<const char*> RequestedExtensions, bool DebugModeOn);
};

