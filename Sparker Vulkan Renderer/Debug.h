#pragma once

#include <iostream>
#include <string>

#include <vulkan/vulkan.h>

using std::string;
using std::cout;
using std::endl;

namespace Graphics {

	enum Severity {
		SP_MESSAGE_INFO,
		SP_MESSAGE_WARNING,
		SP_MESSAGE_ERROR,
		SP_MESSAGE_FATAL
	};

	enum exitCode {
		SP_EXIT_SUCCESS,
		SP_EXIT_FAILED_TO_CREATE_INSTANCE = 100,
		SP_EXIT_FAILED_TO_CREATE_WINDOW_SURFACE = 101,
		SP_EXIT_NO_VALID_GPU = 102,
		SP_EXIT_FAILED_TO_CREATE_DEBUG_MESSENGER = 300,
		SP_EXIT_VULKAN_NOT_SUPPORTED_GLFW = 200
	};

	namespace Debug{
		
		namespace Console {


			void consoleWrite(Severity msgLevel, string message);


			void checkResult(Severity msgLevel, VkResult result, string successMessage, string failMessage);
			void checkResult(Severity msgLevel, VkResult result, string successMessage, string failMessage, exitCode errorCode);

			void exitWithMsg(string message, exitCode errorCode);
			
			VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		}

	}
}
