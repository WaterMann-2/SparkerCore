#include "SpBuffer.h"

SpBuffer::operator VkBuffer(){
	return buffer;
}

/// <summary>
/// 
/// </summary>
/// <param name="usage">| Automatically includes Transfer/Destination bit, ONLY INCLUDE INTENDED USE BIT (I.E. VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)</param>
void SpBuffer::create(VkPhysicalDevice pPhysicalDeivce, VkDevice pDevice, SpBufferCommand& bufferCommand, VkDeviceSize bufferSize, void* pBufferData, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) {
	device = pDevice;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	createBuffer(pPhysicalDeivce, pDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, pBufferData, (size_t)bufferSize);
	vkUnmapMemory(device, stagingBufferMemory);

	createBuffer(pPhysicalDeivce, pDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | usage, properties, buffer, bufferMemory);

	bufferCommand.CopyBuffer(stagingBuffer, buffer, bufferSize);
	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void SpBuffer::destroy() {
	vkDestroyBuffer(device, buffer, nullptr);
	vkFreeMemory(device, bufferMemory, nullptr);
}



void SpBuffer::createBuffer(VkPhysicalDevice pPhysicalDeivce, VkDevice pDevice, VkDeviceSize bufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkBufferCreateInfo bufferCreateInfo{};
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.size = bufferSize;
	bufferCreateInfo.usage = usage;
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	VkResult result = vkCreateBuffer(pDevice, &bufferCreateInfo, nullptr, &buffer);
	SpDebug::SpConsole::vkResultExitCheck(result, "Failed to create buffer!", "Created buffer", SpDebug::SP_EXIT_FAILED_TO_CREATE_BUFFER);


	VkMemoryRequirements bufferMemoryRequirements;
	vkGetBufferMemoryRequirements(pDevice, buffer, &bufferMemoryRequirements);


	VkMemoryAllocateInfo allocationInfo{};
	allocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocationInfo.allocationSize = bufferMemoryRequirements.size;
	allocationInfo.memoryTypeIndex = SpCommon::Memory::findMemoryType(pPhysicalDeivce, bufferMemoryRequirements.memoryTypeBits, properties);

	result = vkAllocateMemory(pDevice, &allocationInfo, nullptr, &bufferMemory);
	SpDebug::SpConsole::vkResultExitCheck(result, "Failed to allocate buffer memory!", "Allocated buffer memory", SpDebug::SP_EXIT_FAILED_TO_ALLOCATE_BUFFER_MEMORY);

	vkBindBufferMemory(pDevice, buffer, bufferMemory, 0);
}

///-------------------------------------------------------------------

void SpBufferCommand::CreateCommandPool(VkPhysicalDevice physicalDevice, VkDevice inDevice, QueueFamilyIndices queueFamily, VkQueue submitQueue) {
	device = inDevice;
	submissionQueue = submitQueue;

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamily.graphicsFamily.value();

	VkResult result = vkCreateCommandPool(inDevice, &poolInfo, nullptr, &commmandPool);

	SpDebug::SpConsole::vkResultExitCheck(result, "Failed to make command pool for Buffer Transfers", "Created command pool for Buffer Transfers", SpDebug::SP_EXIT_FAILED_TO_CREATE_COMMAND_POOL);
}

/// <summary>
/// 
/// </summary>
/// <param name="submitQueue">Graphics / Transfer / Compute queues</param>
void SpBufferCommand::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commmandPool;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	
	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0;
	copyRegion.dstOffset = 0;
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(submissionQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(submissionQueue);
	vkFreeCommandBuffers(device, commmandPool, 1, &commandBuffer);
}