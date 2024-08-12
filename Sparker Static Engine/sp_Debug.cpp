#include "sp_Debug.h"

void sp_Console::consoleWrite(uint8_t severity, string message){
	switch (severity) {
	case SP_INFO:
		cout << "[INFO] " << message << endl;
		break;

	case SP_WARNING:
		cout << "[WARNING] " << message << endl;
		break;

	case SP_ERROR:
		cout << "[ERROR] " << message << endl;
		break;

	case SP_FATAL:
		cout << "[FATAL] " << message << endl;

		//TODO runtime error on a fatal 
		break;
	}
}

void sp_Console::vkResultCheck(uint8_t failSeverity, VkResult result, string successMessage, string failMessage, bool exitProgram, int32_t exitCode){
	if (result != VK_SUCCESS) {
		consoleWrite(failSeverity, failMessage);
		consoleWrite(failSeverity, "Error Code: " + result);
		assert(exitProgram);
	}
	else {
		consoleWrite(SP_INFO, successMessage);
	}


}

void sp_Console::fatalExit(bool failCondition, string failMessage, int32_t exitCode){
	if (failCondition) {
		DCout(SP_FATAL, failMessage);
		std::exit(exitCode);
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL sp_Debug::VkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData){

	std::cerr << "Validation layer: " << pCallbackData->pMessage << endl;
	if (messageSeverity >= SP_VK_WARNING) {
	}
	

	return VK_FALSE;
}
