#include "sp_Primitive.h"

VkVertexInputBindingDescription  Vertex::getBindingDescription() {
	VkVertexInputBindingDescription  bindingDescription{};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> Vertex::getAttributeDescriptions() {
	std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions{};

	getAttributeDescriptions[0].binding = 0;
	getAttributeDescriptions[0].location = 0;
	getAttributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	getAttributeDescriptions[0].offset = offsetof(Vertex, pos);

	getAttributeDescriptions[1].binding = 0;
	getAttributeDescriptions[1].location = 1;
	getAttributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;

	getAttributeDescriptions[2].binding = 0;
	getAttributeDescriptions[2].location = 2;
	getAttributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
	getAttributeDescriptions[2].offset = offsetof(Vertex, texCoord);

	getAttributeDescriptions[2].binding = 0;
	getAttributeDescriptions[2].location = 2;
	getAttributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
	getAttributeDescriptions[2].offset = offsetof(Vertex, texCoord);

	return getAttributeDescriptions;
}
