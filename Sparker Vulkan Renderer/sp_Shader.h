#pragma once

#include "sp_VulkanIncludes.h"

namespace sp_Vulkan {

	enum sp_shaderType {
		VERTEX,
		FRAGMENT
	};

	struct sp_Shader {
		VkShaderModule module;

	};

	struct sp_ShaderCreateInfo {
		VkShaderModuleCreateInfo info{};
	};

	VkShaderModule createShaderModule(VkDevice device, sp_ShaderCreateInfo* createInfo, sp_Shader* shader, VkAllocationCallbacks* callback);
}