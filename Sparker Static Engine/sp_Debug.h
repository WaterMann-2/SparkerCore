#ifndef SP_DEBUG_H
#define SP_DEBUG_H

#ifdef _DEBUG
	#define DCout(severity, message)  sp_Console::consoleWrite(severity, message)
	//#define VkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram, exitCode) sp_Console::vkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram, exitCode)
	//#define VkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram) sp_Console::vkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram, 0);
	#define FatalExit(failOnTrue, failMessage, failCode) sp_Console::fatalExit(failOnTrue, failMessage, failCode);
#else
	#define DCout(severity, message) do {} while(false)
	#define VkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram, exitCode)
	#define VkResultCheck(failSeverity, result, SuccessMessage, FailMessage, ExitProgram)
	#define FatalExit(condition, failMessage, failCode)
#endif




#define _CRT_SECURE_NO_WARNINGS



#include <iostream>
#include <string>
#include <cassert>

#include <vector>

#include "sp_Severity.h"

#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

using std::string;

using std::cout;
using std::endl;

class sp_Debug{

public:

	static VKAPI_ATTR VkBool32 VKAPI_CALL VkDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

};

class sp_Console {

public:

	static void consoleWrite(uint8_t severity, string message);
	static void vkResultCheck(uint8_t failSeverity, VkResult result, const char* SuccessMessage, const char* FailMessage);
	static void vkResultCheck(uint8_t failSeverity, VkResult result, const char* SuccessMessage, const char* FailMessage, int exitCode);
	static void fatalExit(bool condition, string failMessage, int exitCode);
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