#include <iostream>

#include "Sparker Engine.h"

int main() {
	sp_Window window;
	sp_Vulkan vulkan;
	sp_EnterInfo enterInfo;

	{ //Startup function
	sp_Enter startup(enterInfo, vulkan, window);}
	

	while (!glfwWindowShouldClose(window)) {
		
		vulkan.drawFrame();
		window.endFrame();
	}

	sp_ExitInfo exitInfo;
	{//Exit
		sp_Exit exit(exitInfo, window, vulkan);}

}