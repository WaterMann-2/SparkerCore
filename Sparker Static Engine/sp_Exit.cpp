#include "sp_Exit.h"

sp_Exit::sp_Exit(sp_ExitInfo& info, SpWindow& window, sp_Vulkan& vulkan){
	vulkan.vulkanCleanup();
	window.~SpWindow();;
	glfwTerminate();
}
