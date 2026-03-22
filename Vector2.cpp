#include "Vector2.h"
Vector2::Vector2(GLfloat x, GLfloat y) {
	this->x = x;
	this->y = y;
}
Vector2::Vector2(GLint loc) {
	uniformL = loc;
}
void Vector2::uniform() {
	if (uniformL == -1) {
		throw std::runtime_error("uniform is -1");
	}
	glUniform2f(uniformL, x, y);
}