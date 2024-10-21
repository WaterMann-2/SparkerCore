#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "sp_Debug.h"
#include "Input.h"

class SpWindow{
	
public:
	operator GLFWwindow* ();
	

	bool newWindow(std::string windowName);

	void endFrame();
	
	static void end();
	void destroy();

	void setInput(SpInput* input);

	glm::ivec2 getDimensions();
	bool getFramebufferResized();
	float getDeltaTime();
	GLFWwindow* getGLWindow();

	bool mouseEnabled();
	void enableMouse(bool status);

	bool mouseover();
	

private:
	GLFWwindow* window;
	glm::vec2 dimension = glm::vec2(800, 800);

	string WindowName = "Vulkan Moment";

	bool framebufferResized = false;

	float frameTime = 0.0f;
	float lastFrame = 0.0f;

	SpInput* mainInput;

	bool mouseCallbackCalled = false;
	MousePosInfo posInfo;
	MouseAttendanceInfo attendInfo;

	MouseInputs mouseBtnInfo;


	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	static void MouseDeltaCallback(GLFWwindow* window, double xpos, double ypos);
	static void MouseEnteredCallback(GLFWwindow* window, int entered);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	void calcMousedelta();

};

