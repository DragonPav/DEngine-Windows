#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Program.h"
#include "Object3D.h"
#include "Camera.h"
#include "ObjectCreator.h"
#include "CameraControl.h"
#include "StaticModel.h"
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "DEngine", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return 2;
	}
	glfwSetKeyCallback(window, key_callback);
	std::ifstream vertex("vertex.glsl");
	std::ifstream fragment("fragment.glsl");
	Shader vert(&vertex, Shader::Type::Vertex);
	vert.compile();
	Shader frag(&fragment, Shader::Type::Fragment);
	frag.compile();
	Program program(&vert, &frag);
	if (!program.link()) {
		return 3;
	}
	glUseProgram(program.programId);
	Lighting li(Vector3(0.5f, 2, 2), &program);
	li.pointLights[0].position.x = 0.5f;
	li.pointLights[0].position.y = 2;
	li.pointLights[0].position.z = 0;
	RenderUtils re(&program, &li, window);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	Camera cam(&re);
	cam.setPos(Vector3(0.5f, 2, 2));
	Texture red({0xff, 0, 0}, &program, Texture::Config());
	Texture yellow({0xff, 0xff, 0}, &program, Texture::Config());
	BoundingBox bb, bb1;
	Object3D sphere = ObjectCreator::createSphere(Vector3(0, 0, 0), 1.0f, 36, 18, &cam, &red);
	bb = sphere.bounds;
	Object3D box = ObjectCreator::createBoxWireframe(Vector3(bb.getCenter()), Vector3(bb.getSizes()), &cam, &yellow);
	Object3D sphere2 = ObjectCreator::createSphere(Vector3(0, 0, -2), 1.0f, 36, 18, &cam, &red);
	bb1 = sphere2.bounds;
	Object3D box1 = ObjectCreator::createBoxWireframe(Vector3(bb1.getCenter()), Vector3(bb1.getSizes()), &cam, &yellow);
	std::vector<Object3D> s;
	s.push_back(sphere);
	s.push_back(sphere2);
	StaticModel sm(&cam, &re, s);
	sphere.dispose();
	sphere2.dispose();
	cam.perspective(80, (float) width / (float) height, 0.1f, 100.0f);
	CameraControl cc(&re);
	cam.setCameraControl(&cc);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sm.begin();
		sm.render();
		sm.end();
		if (cam.isMouseOverBoundingBox(cam.mousePosX, cam.mousePosY, &bb)) {
			box.begin();
			box.render();
			box.end();
		}
		if (cam.isMouseOverBoundingBox(cam.mousePosX, cam.mousePosY, &bb1)) {
			box1.begin();
			box1.render();
			box1.end();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	sm.dispose();
	box.dispose();
	box1.dispose();
	red.dispose();
	yellow.dispose();
	program.deleteProgram();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}