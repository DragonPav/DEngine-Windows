#pragma once
#include "Matrix4.h"
#include "RenderUtils.h"
#include "CameraControl.h"
#include <GL/glew.h>
class RenderUtils;
class CameraControl;
class Camera {
public:
	Matrix4 projection;
	Matrix4 view;
	Vector3 camPos;
	Vector3 lookAtPos;
	bool autoUpdate = true;
	RenderUtils* rendUtils = nullptr;
	void ortho(float left, float right, float bottom, float top, float near, float far);
	void perspective(float fov, float aspectRatio, float near, float far);
	void lookAt(Vector3 pos);
	void setPos(Vector3 pos);
	void update();
	void setCameraControl(CameraControl* cc);
	Camera() = delete;
	Camera(RenderUtils* re);
};