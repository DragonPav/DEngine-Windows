#pragma once
#include "Lighting.hpp"
#include <GLFW/glfw3.h>
class RenderUtils {
public:
	GLFWwindow* window = nullptr;
	GLuint VAO = 0, VBO = 0, EBO = 0, VBO_texture = 0, VBO_normal = 0;
	Lighting* lighting = nullptr;
	Program* p = nullptr;
	GLint unifor = -1;
	void init() {
		std::cout << "Initializing RenderUtils..." << std::endl;
		std::cout << "------------------------" << std::endl;
		std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		std::cout << "Width: " << width << std::endl;
		std::cout << "Height: " << height << std::endl;
		GLuint tmpBuf[1];
		glGenVertexArrays(1, tmpBuf);
		VAO = tmpBuf[0];
		glGenBuffers(1, tmpBuf);
		VBO = tmpBuf[0];
		glGenBuffers(1, tmpBuf);
		VBO_texture = tmpBuf[0];
		if (lighting != nullptr) {
			glGenBuffers(1, tmpBuf);
			VBO_normal = tmpBuf[0];
		}
		glGenBuffers(1, tmpBuf);
		EBO = tmpBuf[0];
		if (glGetError() != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << glGetError() << std::endl;
		}
	}
	void bind(GLfloat* vertices, GLuint* indices, GLfloat* tex, GLuint vertexBufSize, GLuint indexBufSize, GLuint texBufSize, GLfloat* normal, GLuint normalBufferSize) {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexBufSize, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
		glBufferData(GL_ARRAY_BUFFER, texBufSize, tex, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		if (lighting != nullptr) {
			glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);
			glBufferData(GL_ARRAY_BUFFER, normalBufferSize, normal, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(2);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufSize, indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		if (lighting != nullptr) {
			lighting->bind();
		}
	}
	void dispose() {
		std::cout << "Destroying RenderUtils..." << std::endl;
		glDeleteVertexArrays(1, &VAO);
		if (VBO_normal != 0) {
			GLuint tmpBuf[] = { VBO, EBO, VBO_texture, VBO_normal};
			glDeleteBuffers(4, tmpBuf);
		} else {
			GLuint tmpBuf[] = { VBO, EBO, VBO_texture };
			glDeleteBuffers(3, tmpBuf);
		}
	}
	RenderUtils() {}
	RenderUtils(Program* program, Lighting* li, GLFWwindow* window) {
		p = program;
		lighting = li;
		this->window = window;
	}
};