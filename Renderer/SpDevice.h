#pragma once

#include <SpDebug.h>
#include "SpCommon.h"

namespace SpDevice {

	struct SwapchainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		vector<VkSurfaceFormatKHR> formats;
		vector<VkPresentModeKHR> presentModes;

		bool compatiable() { return !formats.empty() && !presentModes.empty(); }
	};

	struct SpPhysicalDeviceInfo {
		VkPhysicalDevice device;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		vector<VkExtensionProperties> extensionProperties;
		vector<const char*> extensionNames;
		
		SwapchainSupportDetails swapchainSupportDetails;
		QueueFamilyIndices queueFamily;
	};

	struct SpLogicalDeviceInfo {
		VkDevice device;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkQueue transferQueue;
		//VkQueue computeQueue;
	};


	class SpPhysicalDevice {
	public:
		VkPhysicalDevice getVkDevice();
		/// <summary>
		/// "PhysicalDeivceInfo" has: VkDevice, VkDeviceProperties, VkDeviceFeatures
		/// </summary>
		SpPhysicalDeviceInfo* getPhysicalDeviceInfo();

		
		void CreatePhysicalDevice(VkInstance Instance, vector<const char*> RequiredExtensions, VkSurfaceKHR Surface);


		
	private:
		vector<const char*> requiredExtensions;

		SpPhysicalDeviceInfo deviceInfo;

		VkInstance instance;
		VkSurfaceKHR surface;

	private:

		void pickDevice();

		bool isDeviceSuitable(SpPhysicalDeviceInfo& info);
		bool checkDeviceExtensions(SpPhysicalDeviceInfo& info);
		void querySwapchainSupport(SpPhysicalDeviceInfo& info);

		/// <summary>
		/// Unsupported for now. Does nothing.
		/// </summary>
		static int rateDevice(SpPhysicalDeviceInfo& info);
	};

	class SpLogicalDevice {
	public:

		void CreateLogicalDevice(VkInstance Instance, SpPhysicalDeviceInfo& PhysicalDeviceInfo, vector<const char*> enabledValidationLayerNames);

	private:
		VkInstance instance;
		SpPhysicalDeviceInfo* pPhysicalDeviceInfo;

		SpLogicalDeviceInfo deviceInfo;


		
	private:

		void createDevice(vector<const char*> enabledValidationLayerNames);
	};
}


