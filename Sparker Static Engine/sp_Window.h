#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class sp_Window{
	
public:
	glm::vec2 dimension = glm::vec2(800, 800);

	void destroy();
	
	operator GLFWwindow* () {
		return window;
	}

	static sp_Window newWindow(std::string windowName);

	GLFWwindow* getGLWindow();

	void endFrame() {
		glfwPollEvents();
	}
	
	static void end();


private:
	GLFWwindow* window;

	std::string WindowName = "Vulkan Moment";
};

