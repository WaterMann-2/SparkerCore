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

VKAPI_ATTR VkBool32 VKAPI_CALL sp_Debug::VkDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData){

	std::cerr << "Validation layer: " << pCallbackData->pMessage << endl;
	if (messageSeverity >= SP_VK_WARNING) {
	}
	

	return VK_FALSE;
}
