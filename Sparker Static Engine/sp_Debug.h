#ifndef SP_DEBUG_H
#define SP_DEBUG_H

#ifdef _DEBUG
	#define DCout(severity, message)  SpConsole::consoleWrite(severity, message)
#else
	#define DCout(severity, message) do {} while(false)
#endif


#define _CRT_SECURE_NO_WARNINGS



#include <iostream>
#include <string>
#include <cassert>

#include <vector>

#include "sp_Severity.h"

#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::string;

using std::cout;
using std::endl;

class SpDebug{

public:

	static VKAPI_ATTR VkBool32 VKAPI_CALL VkDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	static string vec2ToStr(glm::vec2 vector);
	static string vec3ToStr(glm::vec3 vector);
};

class SpConsole {

public:

	static void consoleWrite(uint8_t severity, string message);
	static void vkResultCheck(uint8_t severity, VkResult result, string successMessage, string failMessage);
	static void vkResultCheck(uint8_t severity, VkResult result, string successMessage, string failMessage, int exitCode);

	static void fatalExit(bool condition, string extMessage, int exitCode);
};

struct sp_ErrorLocation {
	const char* fileName;
	unsigned int lineNumber;
	const char* functionName;

	string toString() {
		return (fileName + ' ' + std::to_string(lineNumber) + ' ' + functionName).c_str();
	}
};

#endif // !SP_DEBUG_H