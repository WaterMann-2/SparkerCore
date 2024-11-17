#include "sp_Window.h"

bool SpWindow::getFramebufferResized() {
	if (framebufferResized) {
		framebufferResized = false;
		return true;
	}
	return false;
}

void SpWindow::destroy(){
	glfwDestroyWindow(window);
}

void SpWindow::setInput(SpInput* input){
	input->setWindow(window);
	mainInput = input;

	mainInput->setPosInfo(&posInfo);
	mainInput->setAttendanceInfo(&attendInfo);
	mainInput->setMouseButtonsInfo(&mouseBtnInfo);
}

SpWindow::operator GLFWwindow* () {
	return window;
}

bool SpWindow::newWindow(std::string windowName){

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	WindowName = windowName;
	window = glfwCreateWindow(dimension.x, dimension.y, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
	
	glfwSetCursorPosCallback(window, MouseDeltaCallback);
	glfwSetCursorEnterCallback(window, MouseEnteredCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	return window;
}

GLFWwindow* SpWindow::getGLWindow() {
	return *&window;
}

bool SpWindow::mouseEnabled(){
	return attendInfo.enabled;
}

void SpWindow::enableMouse(bool status){
	attendInfo.enabled = status;

	if (status) {
		attendInfo.firstMouse = true;

		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		posInfo.position = glm::vec2(xpos, ypos);
		posInfo.lastPos = glm::vec2(xpos, ypos);

		posInfo.delta = glm::vec3(0.0f);
	}

}

bool SpWindow::mouseover(){
	return attendInfo.entered;
}


void SpWindow::endFrame() {
	glfwPollEvents();

	frameTime = glfwGetTime() - lastFrame;
	lastFrame = frameTime + lastFrame;

	calcMousedelta();

	mouseBtnInfo.endFrame();
	//SpConsole::consoleWrite(SP_MESSAGE_INFO, "FRAME ENDED!");
}

void SpWindow::end() {
	glfwTerminate();
}

glm::ivec2 SpWindow::getDimensions(){
	return glm::ivec2((int) dimension.x, (int) dimension.y);
}

float SpWindow::getDeltaTime() {
	return frameTime;
}

void SpWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
	SpWindow* Window = reinterpret_cast<SpWindow*>(glfwGetWindowUserPointer(window));
	Window->framebufferResized = true;
}


void SpWindow::MouseDeltaCallback(GLFWwindow* window, double xpos, double ypos) {
	SpWindow* Window = reinterpret_cast<SpWindow*>(glfwGetWindowUserPointer(window));

	if (!Window->attendInfo.enabled) {
		return;
	}

	if (!Window->attendInfo.entered) return;

	float xPos = (float)xpos;
	float yPos = (float)ypos;

	Window->posInfo.position = glm::vec2(xpos, ypos);
	
	Window->mouseCallbackCalled = true;
}

void SpWindow::MouseEnteredCallback(GLFWwindow* window, int entered) {
	SpWindow* Window = reinterpret_cast<SpWindow*>(glfwGetWindowUserPointer(window));
	
	if (entered) {
		Window->attendInfo.entered = true;
		return;
	}

	if (!entered) {
		Window->attendInfo.firstMouse = true;
		Window->attendInfo.entered = false;
		return;
	}
}

void SpWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
	SpWindow* Window = reinterpret_cast<SpWindow*>(glfwGetWindowUserPointer(window));
	
	if (button > 4) {
		SpConsole::consoleWrite(SP_MESSAGE_ERROR, "Mouse button requested is above max of 4 (AKA mouse button 5)");
		return;
	}
	MouseButton& active = *Window->mouseBtnInfo.all[button];

	if (action == GLFW_PRESS && !active.pressed) {
		active.pressed = true;
		active.down = true;
	}
	
	if (action == GLFW_RELEASE) {
		active.pressed = false;
		active.up = true;
	}
}


void SpWindow::calcMousedelta(){

	//When the mouse is captured into the screen this is so it doesn't flick the camera
	if (attendInfo.firstMouse && attendInfo.entered == true) {
		posInfo.lastPos = posInfo.position;
		attendInfo.firstMouse = false;
	}

	posInfo.delta = posInfo.position - posInfo.lastPos;

	posInfo.lastPos = posInfo.position;
}
