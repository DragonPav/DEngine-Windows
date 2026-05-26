#pragma once
#include "Camera.h"
#include "RenderUtils.h"
#include <GLFW/glfw3.h>
class Camera;
class RenderUtils;
class CameraControl {
public:
	GLFWwindow* window = nullptr;
	void setup(Camera* camera);
	CameraControl() = delete;
	CameraControl(RenderUtils* renderUtils);
};
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);