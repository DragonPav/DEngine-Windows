#pragma once
#include "Lighting.h"
#include <GLFW/glfw3.h>
class Lighting;
class RenderUtils {
public:
	GLFWwindow* window = nullptr;
	GLuint VAO = 0, VBO = 0, EBO = 0, VBO_texture = 0, VBO_normal = 0;
	Lighting* lighting = nullptr;
	Program* p = nullptr;
	GLint unifor = -1;
	void init();
	void bind(GLfloat* vertices, GLuint* indices, GLfloat* tex, GLuint vertexBufSize, GLuint indexBufSize, GLuint texBufSize, GLfloat* normal, GLuint normalBufferSize);
	void dispose();
	RenderUtils() = delete;
	RenderUtils(Program* program, Lighting* li, GLFWwindow* window);
};