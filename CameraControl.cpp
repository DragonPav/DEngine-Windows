#include "CameraControl.h"
double startX = 0, startY = 0;
Camera* camera = nullptr;
bool pressed = false;
CameraControl::CameraControl(RenderUtils* renderUtils) {
	window = renderUtils->window;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &startX, &startY);
		pressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
		pressed = false;
	}
}
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (pressed) {
		double x = 0;
		double y = 0;
		glfwGetCursorPos(window, &x, &y);
		if (x > startX) {
			if (x - startX >= 80) {
				camera->view.rotate(Vector3(0, 1, 0), (float) (x - startX) / 5000, nullptr);
			}
		}
		else if (x < startX) {
			if (startX - x >= 80) {
				camera->view.rotate(Vector3(0, 1, 0), (float) -(startX - x) / 5000, nullptr);
			}
		}
		if (y > startY) {
			if (y - startY >= 80) {
				camera->view.rotate(Vector3(1, 0, 0), (float) -(startY - y) / 5000, nullptr);
			}
		}
		else if (y < startY) {
			if (startY - y >= 80) {
				camera->view.rotate(Vector3(1, 0, 0), (float) (y - startY) / 5000, nullptr);
			}
		}
	}
}
void CameraControl::setup(Camera* came) {
	camera = came;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
}