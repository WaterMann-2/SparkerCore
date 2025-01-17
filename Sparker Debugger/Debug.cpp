#include "Debug.h"

namespace Debug {

	void SpConsole::consoleWrite(SpMessage severity, string message) {
		switch (severity) {
		case SP_MESSAGE_INFO:
			cout << "[INFO] " << message << endl;
			break;

		case SP_MESSAGE_WARNING:
			cout << "[WARNING] " << message << endl;
			break;

		case SP_MESSAGE_ERROR:
			cout << "[ERROR] " << message << endl;
			break;

		case SP_MESSAGE_FATAL:
			cout << "[FATAL] " << message << endl;

			//TODO runtime error on a fatal 
			break;
		}
	}

	void SpConsole::vkResultCheck(SpMessage severity, VkResult result, string successMessage, string failMessage) {
		if (result == VK_SUCCESS) {
			consoleWrite(SP_MESSAGE_INFO, successMessage);
			return;
		}

		consoleWrite(severity, failMessage);
		consoleWrite(severity, "Vulkan Code: " + std::to_string(result));
	}

	void SpConsole::vkResultCheck(SpMessage severity, VkResult result, string successMessage, string failMessage, int exitCode) {
		if (result == VK_SUCCESS) {
			consoleWrite(SP_MESSAGE_INFO, successMessage);
			return;
		}

		consoleWrite(severity, failMessage);
		consoleWrite(severity, "Vulkan Code: " + std::to_string(result));
		std::exit(exitCode);
	}

	void SpConsole::vkResultExitCheck(VkResult result, string failMessage, SpExitCode exitCode) {
		if (result == VK_SUCCESS) {
			return;
		}

		consoleWrite(SP_MESSAGE_FATAL, failMessage);
		consoleWrite(SP_MESSAGE_FATAL, "Vulkan Code: " + std::to_string(result));
		std::exit(exitCode);
	}

	void SpConsole::vkResultExitCheck(VkResult result, string failMessage, string successMessage, SpExitCode exitCode) {
		if (result == VK_SUCCESS) {
			consoleWrite(SP_MESSAGE_INFO, successMessage);
			return;
		}

		consoleWrite(SP_MESSAGE_FATAL, failMessage);
		consoleWrite(SP_MESSAGE_FATAL, "Vulkan Code: " + std::to_string(result));
		std::exit(exitCode);
	}

	void SpConsole::fatalExit(bool condition, string exitMessage, int exitCode) {
		if (!condition) {
			return;
		}

		consoleWrite(SP_MESSAGE_FATAL, exitMessage);
		std::exit(exitCode);
	}

	void SpConsole::fatalExit(string exitMessage, int exitCode) {
		consoleWrite(SP_MESSAGE_FATAL, exitMessage);
		std::exit(exitCode);
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL SpConsole::VkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData){
		switch (messageSeverity) {

		case SP_VK_VERBOSE:
			SpConsole::consoleWrite(SP_MESSAGE_INFO, string("[VULKAN] ") + pCallbackData->pMessage);
			break;
		case SP_VK_WARNING:
			SpConsole::consoleWrite(SP_MESSAGE_WARNING, string("[VULKAN] ") + pCallbackData->pMessage);
			break;
		case SP_VK_ERROR:
			SpConsole::consoleWrite(SP_MESSAGE_ERROR, string("[VULKAN] ") + pCallbackData->pMessage);
			break;
		}

		return VK_FALSE;
	}

	VkDebugUtilsMessengerCreateInfoEXT SpConsole::PopulateDebugMessenger(){
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = SP_VK_VERBOSE | SP_VK_WARNING | SP_VK_ERROR;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = VkDebugCallback;
		debugCreateInfo.pUserData = nullptr;
		return debugCreateInfo;
	}

}