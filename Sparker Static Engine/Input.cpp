#include "Input.h"

void KeyListener::update(GLFWwindow* window){
	int status = glfwGetKey(window, GlKey);

	down = false;
	up = false;

	if (status == GLFW_PRESS && pressed == false) {
		down = true;
		pressed = true;
	}

	if (status == GLFW_RELEASE) {
		pressed = false;
		up = true;
	}

	

}

void sKeyListener::update(GLFWwindow* window){
	int status = glfwGetKey(window, GlKey);

	pressed = false;

	if (status == GLFW_PRESS) pressed = true;
	//sp_Console::consoleWrite(SP_MESSAGE_INFO, "Key: " + std::to_string(GlKey) + ", Status: " + std::to_string(pressed));
}

void Binding4::update(GLFWwindow* window) {

	North.update(window);
	East.update(window);
	West.update(window);
	South.update(window);

	dir.x = 0;
	dir.y = 0;

	dir.x = (West.pressed) ? -1.0f : 0.0f;
	dir.x = (East.pressed) ? 1.0f : dir.x;


	dir.y = (South.pressed) ? -1.0f : 0.0f;
	dir.y = (North.pressed) ? 1.0f : dir.y;

	glm::normalize(dir);

}

glm::vec2 Binding4::getDir(){
	return dir;
}

void Binding2::update(GLFWwindow* window) {
	HiVal.update(window);
	LoVal.update(window);

	dir = (LoVal.pressed) ? -1.0f : 0.0f;
	dir = (HiVal.pressed) ? 1.0 : dir;
}

SpInput::SpInput(){
	keys.resize(0);
	bind4Keys.resize(0);
	bind2Keys.resize(0);
}

void SpInput::setBoundKeySize(int size) {
	keys.resize(size);
}

void SpInput::setBinding2Size(int size) {
	bind2Keys.resize(size);
}

void SpInput::setBinding4Size(int size) {
	bind4Keys.resize(size);
}

KeyListener* SpInput::addKey(int key){
	KeyListener newKey{};
	newKey.GlKey = key;
	keys[currentCount] = newKey;

#ifdef INPUT_DEBUG
	string message = "Created Binding with glKey " +  std::to_string(key);
	DCout(SP_MESSAGE_INFO, message);
#endif

	currentCount++;
	return &keys[keys.size() - 1];
}

Binding4* SpInput::addBinding4(const char* name, int inNorth, int inSouth, int inEast, int inWest){
	sKeyListener kNorth{};
	sKeyListener kSouth{};
	sKeyListener kEast{};
	sKeyListener kWest{};

	kNorth.GlKey = inNorth;
	kSouth.GlKey = inSouth;
	kEast.GlKey = inEast;
	kWest.GlKey = inWest;

	Binding4 newBind4{};
	newBind4.name = name;
	newBind4.North = kNorth;
	newBind4.South = kSouth;
	newBind4.East = kEast;
	newBind4.West = kWest;
	
	bind4Keys[currentCountB4] = newBind4;

#ifdef INPUT_DEBUG
	string message = "Created Binding4 " + string(name) + " with bindings N: " + std::to_string(inNorth) + ", S: " + std::to_string(inSouth) + ", E: " + std::to_string(inWest);
	DCout(SP_MESSAGE_INFO, message);
#endif

	currentCountB4++;
	return &bind4Keys[currentCountB4 -1];
}

Binding2* SpInput::addBinding2(const char* name, int inHiVal, int inLoVal){
	sKeyListener kLoVal{};
	sKeyListener kHiVal{};

	kLoVal.GlKey = inLoVal;
	kHiVal.GlKey = inHiVal;

	Binding2 newBind2{};
	newBind2.name = name;
	newBind2.LoVal = kLoVal;
	newBind2.HiVal = kHiVal;

	bind2Keys[currentCountB2] = newBind2;

#ifdef INPUT_DEBUG
	string message = "Created Binding4 " + string(name) + " with bindings N: " + std::to_string(inHiVal) + ", S: " + std::to_string(inLoVal);
	DCout(SP_MESSAGE_INFO, message);
#endif

	currentCountB2++;
	return &bind2Keys[currentCountB2 - 1];
}

void SpInput::bruteListen(){
	if (keys.empty()) goto VectorListen;
	for (KeyListener& key : keys) {
		key.update(window);
	}

VectorListen:
	if (bind4Keys.empty()) goto ScalarListen;
	for (Binding4& bKey : bind4Keys) {
		bKey.update(window);
	}

ScalarListen:
	if (bind2Keys.empty()) return;
	for (Binding2& scalKey : bind2Keys) {
		scalKey.update(window);
	}
}

void SpInput::setWindow(GLFWwindow* inWindow){
	window = inWindow;
}

void SpInput::setPosInfo(MousePosInfo* info){
	posInfo = info;
}

void SpInput::setAttendanceInfo(MouseAttendanceInfo* info){
	attendInfo = info;
}

glm::vec2 SpInput::getMouseDelta(){
	return posInfo->delta;
}

glm::vec2 SpInput::getMousePosition(){
	return posInfo->position;
}

void SpInput::debugMouseInfo(){
	string message = "Mouse Position: " + SpDebug::vec2ToStr(posInfo->position) + ". Old Mouse Position: " + SpDebug::vec2ToStr(posInfo->lastPos) + ". Mouse Delta: " + SpDebug::vec2ToStr(posInfo->delta) + ". First Mouse: " + std::to_string(attendInfo->firstMouse) + ". Mouse Entered: " + std::to_string(attendInfo->entered) + ".\n";


	SpConsole::consoleWrite(SP_MESSAGE_INFO, message);
}


