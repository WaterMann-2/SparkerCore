#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vulkan/vulkan.h>

#include "sp_Debug.h"
#include "sp_VkStructs.h"
#include "sp_Primitive.h"

using std::vector;
using std::string;

namespace sp_Primitive {

	class Mesh{

	public:

		void loadFromFile(const char* filePath);

	private:
		vector<Vertex> vertices;
		vector<uint32_t> indices;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;


	};
}

