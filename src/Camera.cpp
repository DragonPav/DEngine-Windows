#include "Camera.h"
void Camera::ortho(float left, float right, float bottom, float top, float near, float far) {
	projection.values = glm::ortho(left, right, bottom, top, near, far);
}
void Camera::perspective(float fov, float aspectRatio, float near, float far) {
	projection.values = glm::perspective(fov, aspectRatio, near, far);
}
void Camera::lookAt(Vector3 pos) {
	lookAtPos = pos;
	view.values = glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(lookAtPos.x, lookAtPos.y, lookAtPos.z), glm::vec3(0, -1.0f, 0));
}
void Camera::setPos(Vector3 pos) {
	camPos = pos;
	view.values = glm::lookAt(glm::vec3(camPos.x, camPos.y, camPos.z), glm::vec3(lookAtPos.x, lookAtPos.y, lookAtPos.z), glm::vec3(0, -1.0f, 0));
}
void Camera::update() {
	projection.uniform();
	view.uniform();
}
void Camera::setCameraControl(CameraControl* cc) {
	cc->setup(this);
}
Camera::Camera(RenderUtils* re) {
	rendUtils = re;
	projection = Matrix4(glGetUniformLocation(re->p->programId, "projection"));
	view = Matrix4(glGetUniformLocation(re->p->programId, "view"));
	camPos = Vector3(0, 0, 2);
	lookAtPos = Vector3(0, 0, 0);
}