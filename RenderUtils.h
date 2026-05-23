#pragma once
#include "Lighting.h"
#include "ObjectBuffer.h"
#include <GLFW/glfw3.h>
class Lighting;
class RenderUtils {
public:
	GLFWwindow* window = nullptr;
	Lighting* lighting = nullptr;
	Program* p = nullptr;
	ObjectBuffer createStaticVAO(GLfloat* vertices, GLuint* indices, GLfloat* tex, GLfloat* normal, GLuint vertexBufSize, GLuint indexBufSize, GLuint texBufSize, GLuint normalBufferSize);
	RenderUtils() = delete;
	RenderUtils(Program* program, Lighting* li, GLFWwindow* window);
};