#pragma once

#include <SpDebug.h>

struct WindowCreateInfo {
	string name;
	bool mainWindow;
	bool fullscreen;
	bool resizable;
	VkInstance instance;
	uint16_t* startingScreen;
	int* width;
	int* height;
};

class SpWindow {
public:
	GLFWwindow* glWindow();
	VkSurfaceKHR windowSurface();

	SpWindow(WindowCreateInfo WindowCreateInfo);


private:
	GLFWwindow* window;
	string WindowName;
	bool isMainWindow;
	bool isFullscreen;
	VkExtent2D extent;

	VkInstance instance;

	VkSurfaceKHR surface;
	VkSurfaceCapabilitiesKHR surfaceCapabilities;

	bool framebufferResized = false;

	void createSurface();
};