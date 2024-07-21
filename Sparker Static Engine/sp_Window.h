#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "sp_Debug.h"

class sp_Window{
	
public:
	bool getFramebufferResized() {
		if (framebufferResized) {
			framebufferResized = false;
			return true;
		}
		return false;
	}

	void destroy();
	
	operator GLFWwindow* () {
		return window;
	}

	bool newWindow(std::string windowName);

	GLFWwindow* getGLWindow();

	void endFrame() {
		glfwPollEvents();
	}
	
	static void end();


private:
	GLFWwindow* window;
	glm::vec2 dimension = glm::vec2(800, 800);

	string WindowName = "Vulkan Moment";

	bool framebufferResized = false;

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

