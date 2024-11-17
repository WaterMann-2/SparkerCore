#include "Sparker Engine.h"

#include <iostream>



int main() {
	SpConsole::consoleWrite(SP_MESSAGE_INFO, "Program started!");
	SpWindow window;
	sp_Vulkan vulkan;
	sp_EnterInfo enterInfo;
	SpInput mainInput;


	{ //Startup function
	sp_Enter startup(enterInfo, vulkan, window, mainInput);}
	

	mainInput.setBoundKeySize(1);
	mainInput.setBinding2Size(2);
	mainInput.setBinding4Size(1);

	Binding4* movement = mainInput.addBinding4("Movement", GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_A);
	Binding2* vertical = mainInput.addBinding2("Vertical", GLFW_KEY_SPACE, GLFW_KEY_C);
	Binding2* speedKey = mainInput.addBinding2("Speed", GLFW_KEY_LEFT_SHIFT, GLFW_KEY_LEFT_CONTROL);

	KeyListener* mouseToggleBtn = mainInput.addKey(GLFW_KEY_ESCAPE);

	vec2* moveDir = &movement->dir;
	float* vert = &vertical->dir;
	//DCout(SP_MESSAGE_INFO, std::to_string(*vert));
	float* speed = &speedKey->dir;

	Camera cam(glm::vec3(2.0f), glm::vec3(glm::pi<float>() * 6 / 5, 0, glm::pi<float>() / 4), glm::radians(60.0f), glm::ivec2(window.getDimensions()), 0.1f, 100.0f);
	
	vulkan.cam = &cam;

	float baseMSens = 5.0f;
	float movementSensitivity = 5.0f;

	float sensitivity = 0.01f;
	//todo

	while (!glfwWindowShouldClose(window)) {
		mainInput.bruteListen();
		float deltaTime = window.getDeltaTime();
		baseMSens += *speed * deltaTime;
		movementSensitivity = baseMSens * deltaTime;
		

		if (mouseToggleBtn->down) {
			window.enableMouse(false);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		/*
		string message = "M1 Down: " + std::to_string(mainInput.getMouseButtonInfo(0).down) + ". M1 Hold: " + 
			std::to_string(mainInput.getMouseButtonInfo(0).pressed) + ". M1 Up: " + std::to_string(mainInput.getMouseButtonInfo(0).up);*/

		//SpConsole::consoleWrite(SP_MESSAGE_INFO, message);

		if (window.mouseover() && mainInput.getMouseButtonInfo(GLFW_MOUSE_BUTTON_1).pressed) {
			window.enableMouse(true);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}

		if (window.mouseEnabled()) {
			cam.transform.rotation.z -= sensitivity * mainInput.getMouseDelta().x;
			cam.transform.rotation.x += sensitivity * mainInput.getMouseDelta().y;
		}

		cam.transform.position += (movementSensitivity * moveDir->y) * cam.getFront() - (movementSensitivity * moveDir->x) * cam.getRight();
		cam.transform.position.z += *vert * movementSensitivity;

		//SpConsole::consoleWrite(SP_MESSAGE_INFO, "Camera Rotation: " + SpDebug::vec3ToStr(cam.transform.rotation) + ", Camera Front Position: " + SpDebug::vec3ToStr(cam.getFront()));
		//sp_Console::consoleWrite(SP_MESSAGE_INFO, std::to_string(cam.transform.position.x) + " " + std::to_string(cam.transform.position.y) + " " + std::to_string(cam.transform.position.z));

		vulkan.drawFrame();
		window.endFrame();
	}

	sp_ExitInfo exitInfo;
	{//Exit
		sp_Exit exit(exitInfo, window, vulkan);}

}