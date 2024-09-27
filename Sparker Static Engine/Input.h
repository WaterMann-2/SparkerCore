#pragma once

#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>

#include "sp_Debug.h"

using std::vector;

#define INPUT_DEBUG

struct MousePosInfo {
	glm::vec2 lastPos = glm::vec2(0.0f);
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 delta = glm::vec2(0.0f);
};

struct MouseAttendanceInfo {
	bool enabled = true;
	bool firstMouse = true;
	bool entered = false;
};

struct KeyListener {
	int GlKey;
	bool enabled = false;

	bool down;
	bool pressed;
	bool up;

	void update(GLFWwindow* window);
};


/// <summary>
/// Lightweight struct, easier call
/// Intended for multi key bindings
/// </summary>
struct sKeyListener {
	int GlKey;
	
	bool pressed;

	void update(GLFWwindow* window);
};

/// <summary>
/// Vec2 value
/// </summary>
struct Binding4 {
	string name;
	sKeyListener North;
	sKeyListener East;
	sKeyListener South;
	sKeyListener West;

	glm::vec2 dir;

	void update(GLFWwindow* window);

	glm::vec2 getDir();
};

/// <summary>
/// Scalar value
/// </summary>
struct Binding2 {
	string name;
	sKeyListener HiVal;
	sKeyListener LoVal;

	float dir;

	void update(GLFWwindow* window);
};

class SpInput {
public:

	SpInput();

	void setBoundKeySize(int size);
	void setBinding2Size(int size);
	void setBinding4Size(int size);

	KeyListener* addKey(int key);

	Binding4* addBinding4(const char* name, int north, int south, int east, int west);
	Binding2* addBinding2(const char* name, int inHiVal, int inLoVal);

	void bruteListen();

	void setWindow(GLFWwindow* inWindow);
	void setPosInfo(MousePosInfo* info);
	void setAttendanceInfo(MouseAttendanceInfo* info);

	glm::vec2 getMouseDelta();
	glm::vec2 getMousePosition();


	void debugMouseInfo();


private:
	GLFWwindow* window = nullptr;
	
	vector<KeyListener> keys;
	int maxElementsKeys = 0;
	int currentCount = 0;

	vector<Binding4> bind4Keys;
	int maxElementsBind4 = 0;
	int currentCountB4 = 0;

	vector<Binding2> bind2Keys;
	int maxElementsBind2 = 0;
	int currentCountB2 = 0;
	
	vector<sKeyListener> testKeys;

	

	MousePosInfo* posInfo;
	MouseAttendanceInfo* attendInfo;
};

