#include "sp_Exit.h"

sp_Exit::sp_Exit(sp_ExitInfo& info, sp_Window& window, sp_Vulkan& vulkan){
	vulkan.vulkanCleanup();
	window.~sp_Window();;
	glfwTerminate();
}
