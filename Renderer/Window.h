#pragma once

#include <Debug.h>

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

class Window {
public:

	Window(WindowCreateInfo WindowCreateInfo);

	VkSurfaceKHR* windowSurface();

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