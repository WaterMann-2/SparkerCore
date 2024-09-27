#include "sp_Debug.h"

void SpConsole::consoleWrite(uint8_t severity, string message){
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

void SpConsole::vkResultCheck(uint8_t severity, VkResult result, string successMessage, string failMessage){
	if (result == VK_SUCCESS) {
		consoleWrite(SP_MESSAGE_INFO, successMessage);
		return;
	}

	consoleWrite(severity, failMessage);
	consoleWrite(severity, "Vulkan Code: " + std::to_string(result));
}

void SpConsole::vkResultCheck(uint8_t severity, VkResult result, string successMessage, string failMessage, int exitCode) {
	if (result == VK_SUCCESS) {
		consoleWrite(SP_MESSAGE_INFO, successMessage);
		return;
	}

	consoleWrite(severity, failMessage);
	consoleWrite(severity, "Vulkan Code: " + std::to_string(result));
	std::exit(exitCode);
}

void SpConsole::fatalExit(bool condition, string exitMessage, int exitCode){
	if (!condition) {
		return;
	}

	consoleWrite(SP_MESSAGE_FATAL, exitMessage);
	std::exit(exitCode);
}


VKAPI_ATTR VkBool32 VKAPI_CALL SpDebug::VkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData){

	std::cerr << "Validation layer: " << pCallbackData->pMessage << endl;
	if (messageSeverity >= SP_VK_WARNING) {
	}
	

	return VK_FALSE;
}

string SpDebug::vec2ToStr(glm::vec2 vector){
	string message = '('+std::to_string(vector.x) + ", " + std::to_string(vector.y) + ')';
	return message;
}

string SpDebug::vec3ToStr(glm::vec3 vector) {
	string message = '(' + std::to_string(vector.x) + ", " + std::to_string(vector.y) + ", " + std::to_string(vector.z) + ')';
	return message;
}