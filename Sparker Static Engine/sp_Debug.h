#ifndef SP_DEBUG_H
#define SP_DEBUG_H

#ifdef _DEBUG
	#define DCout(severity, message)  sp_Console::consoleWrite(severity, message)
#else
	#define DCout(severity, message) do {} while(false)
	#define VkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram, exitCode)
	#define VkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram)
	#define FatalExit(condition, failMessage, failCode)
#endif




#define _CRT_SECURE_NO_WARNINGS



#include <iostream>
#include <optional>
#include <set>
#include <string>
#include <cassert>

#include <vector>

#include "sp_Severity.h"


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
using std::optional;
using std::set;

using std::cout;
using std::endl;

enum ErrorCode {
	SP_ASSIMP_FLAGS_INCOMPLETE = 510
};

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

	static void consoleWrite(SpMessage severity, string message);
	static void vkResultCheck(SpMessage severity, VkResult result, string successMessage, string failMessage);
	static void vkResultCheck(SpMessage severity, VkResult result, string successMessage, string failMessage, int exitCode);

	static void vkResultExitCheck(VkResult result, string failMessage, SpExitCode exitCode);
	static void vkResultExitCheck(VkResult result, string failMessage, string successMessage, SpExitCode exitCode);
	

	static void fatalExit(bool condition, string exitMessage, int exitCode);
	static void fatalExit(string exitMessage, int exitCode);
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