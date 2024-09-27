#include "sp_Enter.h"

sp_Enter::sp_Enter(sp_EnterInfo& info, sp_Vulkan& vulkan, SpWindow& window, SpInput& input) {
	glfwInit();

	window.newWindow("Vulkan Moment");

	vulkan.vulkanStart(window);

	window.setInput(&input);
	
	
}