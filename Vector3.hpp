#pragma once
#include "Vector2.hpp"
class Vector3 {
public:
	GLfloat x = 0, y = 0, z = 0;
	GLint uniformL = -1;
	void uniform() {
		if (uniformL == -1) {
			throw std::runtime_error("uniform is -1");
		}
		glUniform3f(uniformL, x, y, z);
	}
	Vector3() {}
	Vector3(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(GLint loc) {
		uniformL = loc;
	}
};