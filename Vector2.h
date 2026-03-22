#pragma once
#include <iostream>
#include <GL/glew.h>
class Vector2 {
public:
	GLfloat x = 0, y = 0;
	GLint uniformL = -1;
	void uniform();
	Vector2() = default;
	Vector2(GLfloat x, GLfloat y);
	Vector2(GLint loc);
};