#include "Vector4.h"
Vector4::Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4::Vector4(GLint loc) {
	uniformL = loc;
}
void Vector4::uniform() {
	if (uniformL == -1) {
		throw std::runtime_error("uniform is -1");
	}
	glUniform4f(uniformL, x, y, z, w);
}