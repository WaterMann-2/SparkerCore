#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

using glm::vec2;
using glm::vec3;

struct Vertex {
	vec3 pos;
	vec3 color;

	static VkVertexInputBindingDescription  getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};