#pragma once
#include "Shader.hpp"

class Program {
public:
	GLuint programId = 0;
	Program() {}
	Program(Shader* vertex, Shader* fragment) {
		v = vertex;
		f = fragment;
		if (vertex->type != Shader::Type::Vertex) {
			throw std::runtime_error("vShader must be Vertex");
		}
		if (fragment->type != Shader::Type::Fragment) {
			throw std::runtime_error("fShader must be Fragment");
		}
		programId = glCreateProgram();
		glAttachShader(programId, vertex->shaderId);
		glAttachShader(programId, fragment->shaderId);
		std::cout << "Program with id: " << programId << " created." << std::endl;
	}
	void deleteProgram() {
		glDeleteProgram(programId);
	}
	bool link() {
		glLinkProgram(programId);
		GLint status;
		glGetProgramiv(programId, GL_LINK_STATUS, &status);
		if (status == GL_TRUE) {
			v->deleteShader();
			f->deleteShader();
			std::cout << "Program with id: " << programId << " successfully linked." << std::endl;
			return true;
		}
		else {
			GLchar infoLog[512];
			glGetProgramInfoLog(programId, 512, NULL, infoLog);
			std::cerr << "Failed to link program: " << infoLog << std::endl;
			deleteProgram();
			return false;
		}
	}
private:
	Shader* v = nullptr;
	Shader* f = nullptr;
};