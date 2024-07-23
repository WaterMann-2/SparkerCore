#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

using std::uint32_t;
using std::vector;
using std::string;
using std::to_string;