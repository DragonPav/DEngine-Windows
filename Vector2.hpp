#pragma once
#include <iostream>

#include <GL/glew.h>

class Vector2 {
public:
	GLfloat x = 0, y = 0;
	GLint uniformL = -1;
	void uniform() {
		if (uniformL == -1) {
			throw std::runtime_error("uniform is -1");
		}
		glUniform2f(uniformL, x, y);
	}
	Vector2() {}
	Vector2(GLfloat x, GLfloat y) {
		this->x = x;
		this->y = y;
	}
	Vector2(GLint loc) {
		uniformL = loc;
	}
};