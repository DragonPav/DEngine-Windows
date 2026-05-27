#include "CameraControl.h"
double lastX = 0, lastY = 0;
Camera* camera = nullptr;
bool pressed = false;
float yaw = -90.0f;
float pitch = 0.0f;
float radius = 4.0f;
float sensitivity = 0.01f;
CameraControl::CameraControl(RenderUtils* renderUtils) {
	window = renderUtils->window;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_1) {
		if (action == GLFW_PRESS) {
			glfwGetCursorPos(window, &lastX, &lastY);
			pressed = true;
		}
		else if (action == GLFW_RELEASE) {
			pressed = false;
		}
	}
}
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	camera->mousePosX = (float)xpos;
	camera->mousePosY = (float)ypos;
	if (!pressed || camera == nullptr) return;
	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += (float)xoffset;
	pitch += (float)yoffset;
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	float yawRad = glm::radians(yaw);
	float pitchRad = glm::radians(pitch);
	Vector3 newPos;
	newPos.x = camera->lookAtPos.x + radius * cos(pitchRad) * cos(yawRad);
	newPos.y = camera->lookAtPos.y + radius * sin(pitchRad);
	newPos.z = camera->lookAtPos.z + radius * cos(pitchRad) * sin(yawRad);
	camera->setPos(newPos);
	if (camera->rendUtils->lighting != nullptr) {
		camera->rendUtils->lighting->cameraPos.x = newPos.x;
		camera->rendUtils->lighting->cameraPos.y = newPos.y;
		camera->rendUtils->lighting->cameraPos.z = newPos.z;
	}
}
void CameraControl::setup(Camera* came) {
	camera = came;
	float dx = camera->camPos.x - camera->lookAtPos.x;
	float dy = camera->camPos.y - camera->lookAtPos.y;
	float dz = camera->camPos.z - camera->lookAtPos.z;
	radius = sqrt(dx * dx + dy * dy + dz * dz);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
}
void CameraControl::setSensitivity(float sense) {
	sensitivity = sense;
}