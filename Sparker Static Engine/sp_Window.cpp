#pragma once
#include "sp_Window.h"

void sp_Window::destroy(){
	glfwDestroyWindow(window);
}

bool sp_Window::newWindow(std::string windowName){

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	WindowName = windowName;
	window = glfwCreateWindow(dimension.x, dimension.y, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);


	return window;
}

GLFWwindow* sp_Window::getGLWindow() {
	return *&window;
}

void sp_Window::end() {
	glfwTerminate();
}

void sp_Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	sp_Window* Window = reinterpret_cast<sp_Window*>(glfwGetWindowUserPointer(window));
	Window->framebufferResized = true;
}