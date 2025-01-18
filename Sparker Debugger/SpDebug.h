#pragma once

#include <iostream>
#include <set>
#include <string>
#include <cassert>
#include <vector>
#include <optional>


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::string;
using std::vector;
//using std::optional;
using std::set;

using std::cout;
using std::endl;

namespace SpDebug {

#define SP_VK_VERBOSE VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
#define SP_VK_INFO VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
#define SP_VK_WARNING VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
#define SP_VK_ERROR VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT

	enum SpExitCode {

		Sp_Exit_ValidationLayersUnavailable = 50,
		Sp_Exit_DebugMessengerPtrNotProvided = 51,
		SP_EXIT_FAILED_TO_CREATE_DEBUG_MESSENGER = 52,
		Sp_Exit_InstancePtrNotProvided = 100,
		SP_EXIT_FAILED_TO_CREATE_INSTANCE = 101,
		SP_EXIT_FAILED_TO_CREATE_WINDOW_SURFACE = 105,
		Sp_Exit_FailedToCreateImage = 500,
		Sp_Exit_FailedToAllocateImageMemory = 501,
		Sp_Exit_FailedToCreateImageView = 110,
		SP_EXIT_FAILED_TO_FIND_SUITABLE_MEMORY_TYPE = 150,
		SP_EXIT_FAILED_TO_CREATE_BUFFER = 130,
		SP_EXIT_FAILED_TO_ALLOCATE_BUFFER_MEMORY = 131,
		SP_EXIT_FAILED_TO_CREATE_COMMAND_POOL = 160
	};

	enum SpMessage {
		SP_MESSAGE_INFO,
		SP_MESSAGE_WARNING,
		SP_MESSAGE_ERROR,
		SP_MESSAGE_FATAL,
		SP_VK_RESULT
	};

	class SpConsole {
	public:
		static void consoleWrite(SpMessage severity, string message);
		static void vkResultCheck(SpMessage severity, VkResult result, string successMessage, string failMessage);
		static void vkResultCheck(SpMessage severity, VkResult result, string successMessage, string failMessage, int exitCode);

		static void vkResultExitCheck(VkResult result, string failMessage, SpExitCode exitCode);
		static void vkResultExitCheck(VkResult result, string failMessage, string successMessage, SpExitCode exitCode);


		static void fatalExit(bool condition, string exitMessage, SpExitCode exitCode);
		static void fatalExit(string exitMessage, SpExitCode exitCode);

		static VKAPI_ATTR VkBool32 VKAPI_CALL VkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

		static VkDebugUtilsMessengerCreateInfoEXT PopulateDebugMessenger();
	};

}