#pragma once
#include "sp_Window.h"

void sp_Window::destroy(){
	glfwDestroyWindow(window);
}

sp_Window sp_Window::newWindow(std::string windowName){
	sp_Window window;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window.WindowName = windowName;
	window.window = glfwCreateWindow(window.dimension.x, window.dimension.y, windowName.c_str(), NULL, NULL);
	return window;
}

GLFWwindow* sp_Window::getGLWindow() {
	return *&window;
}

void sp_Window::end() {
	glfwTerminate();
}