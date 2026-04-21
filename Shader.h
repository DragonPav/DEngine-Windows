#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
class Shader {
public:
	enum Type {
		Vertex,
		Fragment
	};
	GLuint shaderId = 0;
	Type type = Vertex;
	Shader(std::ifstream *file, Type type);
	Shader() = default;
	bool compile();
	void deleteShader();
};