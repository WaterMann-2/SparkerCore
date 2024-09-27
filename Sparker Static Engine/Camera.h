#pragma once

#include "sp_Debug.h"
#include "Transform.h"

class Camera {

public:
	spTransform transform;

	/// <summary>
	/// Camera FOV in Radians
	/// </summary>
	float fov = 0.0f;
	float closePlane = 0.0f;
	float farPlane = 0.0f;
	glm::ivec2 size = glm::ivec2(0);



	Camera(glm::vec3 startPos, glm::vec3 startRotation, float fovRads, glm::ivec2 camSize, float nearClipPlane, float farClipPlane);


	void Update();
	glm::mat4 getProj();
	glm::mat4 getView();

	glm::vec3 getFront();
	glm::vec3 getRight();
	glm::vec3 getUp();


private:

	glm::ivec2 pSize = glm::ivec2(-1);
	glm::mat4 camProj = glm::mat4(-1);
	glm::mat4 camView = glm::mat4(-1);
	

	const glm::vec3 Up = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 CameraUp = glm::vec3(0.0f);
	glm::vec3 CameraFront = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 CameraRight = glm::vec3(0.0f);

	float pFov = -1;
	float pClosePlane = -1;
	float pFarPlane = -1;


	bool checkProjectionChanges();

};