#pragma once
#include <iostream>

#include <fstream>

#include <string>

#include <GL/glew.h>
class Shader {
public:
	static enum Type {
		Vertex,
		Fragment
	};
	GLuint shaderId = 0;
	Type type = Vertex;
	Shader(std::ifstream file, Type type) {
		std::string source;
		std::string line;
		while (std::getline(file, line)) {
			source += line + "\r\n";
		}
		file.close();
		switch (type) {
		case Vertex:
			shaderId = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Fragment:
			shaderId = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		this->type = type;
		std::cout << "Shader with type: " << type << " id: " << shaderId << " created." << std::endl;
		const GLchar* buf = source.c_str();
		glShaderSource(shaderId, 1, &buf, NULL);
	}
	Shader() {}
	bool compile() {
		glCompileShader(shaderId);
		GLint status;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
		if (status == GL_TRUE) {
			std::cout << "Shader with id: " << shaderId << " sucessfully compiled" << std::endl;
			return true;
		}
		else {
			GLchar infoLog[512];
			glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
			std::cerr << "Failed to compile shader with id: " << shaderId << " Error log:" << std::endl;
			std::cerr << "-------------------------" << std::endl;
			std::cerr << infoLog << std::endl;
			return false;
		}
	}
	void deleteShader() {
		glDeleteShader(shaderId);
	}
};