#include "Camera.h"

Camera::Camera(glm::vec3 startPos, glm::vec3 startRotation, float fovRads, glm::ivec2 camSize, float nearClipPlane, float farClipPlane){

	transform.position = startPos;
	transform.rotation = startRotation;

	size = camSize;

	fov = fovRads;
	closePlane = nearClipPlane;
	farPlane = farClipPlane;

	Update();
}


void Camera::Update(){
	bool recalculate = checkProjectionChanges();

	//If we have no need to recalculate exit updating
	if (recalculate) {
		camProj = glm::perspective(pFov, pSize.x / (float)pSize.y, pClosePlane, pFarPlane);
		//Need to flip the Y as glm does for OpenGL but not in Vulkan (YIPEE)
		camProj[1][1] *= -1;
	}

	constexpr float pi = glm::pi<float>();


	//To keep the Yaw of the camera always between 0 and 2pi
	//Not required
	if (transform.rotation.z >= 2 * pi) transform.rotation.z -= 2 * pi;
	if (transform.rotation.z < 0) transform.rotation.z += 2 * pi;



	glm::vec3 direction;

	//Pitch
	direction.z = sin(transform.rotation.x);

	//yaw
	direction.x = cos(transform.rotation.z) * cos(transform.rotation.x);
	direction.y = sin(transform.rotation.z) * cos(transform.rotation.x);

	//SpConsole::consoleWrite(SP_MESSAGE_INFO, SpDebug::vec3ToStr(glm::normalize(direction)));

	CameraFront = glm::normalize(direction);
	camView = glm::lookAt(transform.position, transform.position + CameraFront, CameraUp);

	CameraRight = glm::normalize(glm::cross(Up, CameraFront));
	CameraUp = glm::cross(CameraFront, CameraRight);
}

glm::mat4 Camera::getProj(){
	return camProj;
}

glm::mat4 Camera::getView(){
	return camView;
}

glm::vec3 Camera::getFront(){
	return CameraFront;
}

glm::vec3 Camera::getRight() {
	return CameraRight;
}

glm::vec3 Camera::getUp() {
	return CameraUp;
}

bool Camera::checkProjectionChanges(){
	bool recalculate = false;

	if (fov != pFov) {
		recalculate = true;
		pFov = fov;
	}
	if (closePlane != pClosePlane) {
		recalculate = true;
		pClosePlane = closePlane;
	}
	if (farPlane != pFarPlane) {
		recalculate = true;
		pFarPlane = farPlane;
	}
	if (size.x != pSize.x) {
		recalculate = true;
		pSize = size;
	}

	return recalculate;
}
