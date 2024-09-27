#include "Debug.h"

void Graphics::Debug::Console::consoleWrite(Severity msgLevel, string message){
	switch (msgLevel) {
	case SP_MESSAGE_INFO:
		cout << "[INFO][GRAPHICS]: " << message << endl;
		break;

	case SP_MESSAGE_WARNING:
		cout << "[WARNING][GRAPHICS]: " << message << endl;
		break;

	case SP_MESSAGE_ERROR:
		cout << "[ERROR][GRAPHICS]: " << message << endl;
		break;

	case SP_MESSAGE_FATAL:
		cout << "[FATAL][GRAPHICS]: " << message << endl;
		break;
	}
}

void Graphics::Debug::Console::checkResult(Severity msgLevel, VkResult result, string successMessage, string failMessage){
	if (result == VK_SUCCESS) {
		consoleWrite(SP_MESSAGE_INFO, successMessage);
		return;
	}

	consoleWrite(msgLevel, failMessage);
}

void Graphics::Debug::Console::checkResult(Severity msgLevel, VkResult result, string successMessage, string failMessage, exitCode errorCode){
	if (result == VK_SUCCESS) {
		consoleWrite(SP_MESSAGE_INFO, successMessage);
		return;
	}

	consoleWrite(msgLevel, failMessage);
	std::exit(errorCode);
}

void Graphics::Debug::Console::exitWithMsg(string message, exitCode errorCode){
	consoleWrite(SP_MESSAGE_FATAL, message);
	std::exit(errorCode);
}

VKAPI_ATTR VkBool32 VKAPI_CALL Graphics::Debug::Console::VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData){

	std::cerr << "Validation layer: " << pCallbackData->pMessage << endl;

	return VK_FALSE;
}
