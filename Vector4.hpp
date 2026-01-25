#pragma once
#include "Vector2.hpp"
class Vector4 {
	GLfloat x = 0, y = 0, z = 0, w = 0;
	GLint uniformL = -1;
	void uniform() {
		if (uniformL == -1) {
			throw std::runtime_error("uniform is -1");
		}
		glUniform4f(uniformL, x, y, z, w);
	}
	Vector4() {}
	Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
	Vector4(GLint loc) {
		uniformL = loc;
	}
};