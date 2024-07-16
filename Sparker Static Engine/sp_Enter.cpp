#include "sp_Enter.h"

sp_Enter::sp_Enter(sp_EnterInfo& info, sp_Vulkan& vulkan, sp_Window& window) {
	glfwInit();

	window = window.newWindow("Vulkan Moment");

	vulkan.vulkanStart(window);
}