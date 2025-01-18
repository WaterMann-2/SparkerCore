#pragma once

#include <SpDebug.h>

#include "SpCommon.h"

class SpBufferCommand;

class SpBuffer{
public:

	operator VkBuffer();

	void create(VkPhysicalDevice pPhysicalDeivce, VkDevice pDevice, SpBufferCommand& bufferCommand, VkDeviceSize bufferSize, void* pBufferData, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	void destroy();

	VkBuffer buffer;
private:
	VkDevice device;
	VkDeviceMemory bufferMemory;

	static void createBuffer(VkPhysicalDevice pPhysicalDeivce, VkDevice pDevice, VkDeviceSize bufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
};

class SpBufferCommand {
public:
	
	void CreateCommandPool(VkPhysicalDevice physicalDevice, VkDevice inDevice, QueueFamilyIndices queueFamily, VkQueue SubmitQueue);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

private:
	VkDevice device;
	VkCommandPool commmandPool;

	VkQueue submissionQueue;
};
