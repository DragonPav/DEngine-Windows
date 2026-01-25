#pragma once
#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "RenderUtils.hpp"
class Camera {
public:
	Matrix4 projection;
	Matrix4 view;
	Vector3 camPos;
	Vector3 lookAtPos;
	bool autoUpdate = true;
	RenderUtils* rendUtils;
	void ortho(float left, float right, float bottom, float top, float near, float far) {
		projection.values = glm::ortho(left, right, bottom, top, near, far);
	}
	void perspective(float fov, float aspectRatio, float near, float far) {
		projection.values = glm::perspective(fov, aspectRatio, near, far);
	}
	void lookAt(Vector3 pos) {
		lookAtPos = pos;
		view.values = glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(lookAtPos.x, lookAtPos.y, lookAtPos.z), glm::vec3(0, -1.0f, 0));
	}
	void setPos(Vector3 pos) {
		camPos = pos;
		view.values = glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(lookAtPos.x, lookAtPos.y, lookAtPos.z), glm::vec3(0, -1.0f, 0));
	}
	//TODO: add this
	/*
	* void setCameraControl(CameraControl cc) {
	*	cc.setup(this);
	* }
	*/
	void update() {
		projection.uniform();
		view.uniform();
	}
	Camera() {}
	Camera(RenderUtils* re) {
		rendUtils = re;
		projection = Matrix4(glGetUniformLocation(re->p->programId, "projection"));
		view = Matrix4(glGetUniformLocation(re->p->programId, "view"));
		camPos = Vector3(0, 0, 2);
		lookAtPos = Vector3(0, 0, 0);
	}
};