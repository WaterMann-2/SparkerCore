#include "Window.h"

GLFWwindow* SpWindow::glWindow(){
	return window;
}

SpWindow::SpWindow(WindowCreateInfo WindowCreateInfo) {
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	WindowName = WindowCreateInfo.name;
	instance = WindowCreateInfo.instance;
	
	if (WindowCreateInfo.height != nullptr) {
		extent.height = static_cast<uint32_t>(*WindowCreateInfo.height);
	} else {
		extent.height = 500;
	}

	if (WindowCreateInfo.width != nullptr) {
		extent.width = static_cast<uint32_t>(*WindowCreateInfo.width);
	} else {
		extent.width = 500;
	}

	isFullscreen = WindowCreateInfo.fullscreen;
	isMainWindow = WindowCreateInfo.mainWindow;

	//if (WindowCreateInfo.startingScreen == nullptr) WindowCreateInfo.startingScreen = &defaultStartingScreen;

	GLFWmonitor* primaryMoniter = glfwGetPrimaryMonitor();

	window = glfwCreateWindow(extent.width, extent.height, WindowName.c_str(), primaryMoniter, NULL);

	glfwMakeContextCurrent(window);

	createSurface();
}

VkSurfaceKHR SpWindow::windowSurface(){
	return &surface;
}

void SpWindow::createSurface() {
	VkResult surfaceCreateResult = glfwCreateWindowSurface(instance, window, nullptr, &surface);

	SpDebug::SpConsole::vkResultExitCheck(surfaceCreateResult, "Failed to create window surface!", "Created window surface", SpDebug::SP_EXIT_FAILED_TO_CREATE_WINDOW_SURFACE);
}