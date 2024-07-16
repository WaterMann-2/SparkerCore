#ifndef SP_DEBUG_H
#define SP_DEBUG_H

#ifdef _DEBUG
	#define DCout(severity, message)  sp_Console::consoleWrite(severity, message)
#else
	#define DCout(severity, message) do {} while(false)
#endif


#include <iostream>
#include <string>
#include <cassert>

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