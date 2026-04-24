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
	re.init();
	Camera cam(&re);
	cam.setPos(Vector3(0.5f, 2, 2));
	Texture cat(&program, "cat.jpg", Texture::Config());
	Object3D cube = ObjectCreator::createBox(Vector3(2, 0, -2), Vector3(1, 1, 1), &cam, &cat);
	GLubyte color2[] = { 0xff, 0, 0 };
	Texture red(color2, &program, Texture::Config());
	Object3D sphere = ObjectCreator::createSphere(Vector3(0, 0, 0), 1.0f, 20, 20, &cam, &red);
	Object3D sphere2 = ObjectCreator::createSphere(Vector3(0, 0, -2), 1.0f, 20, 20, &cam, &red);
	Object3D* s[] = {&sphere,&sphere2};
	StaticModel sm(&cam, &re, s, 2);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	cam.perspective(80, (float) width / (float) height, 0.1f, 100.0f);
	CameraControl cc(&re);
	cam.setCameraControl(&cc);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		cube.begin();
		cube.render();
		cube.end();
		sm.begin();
		sm.render();
		sm.end();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cube.dispose();
	sphere.dispose();
	cat.dispose();
	red.dispose();
	re.dispose();
	program.deleteProgram();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}