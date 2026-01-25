#pragma once
#include "Vector3.hpp"
#include "Program.hpp"
#include "Object3D.hpp"
class Lighting {
public:
	GLfloat ambientStrength = 0.2f;
	GLfloat specularStrength = 0.5f;
	Vector3 lightPos;
	Vector3 lightColor;
	Vector3 cameraPos;
	GLint ambientStrengthLoc = -1;
	GLint specularStrengthLoc = -1;
	void bind() {
		cameraPos.uniform();
		lightPos.uniform();
		lightColor.uniform();
		if (ambientStrengthLoc != -1) {
			glUniform1f(ambientStrengthLoc, ambientStrength);
		}
		if (specularStrengthLoc != -1) {
			glUniform1f(specularStrengthLoc, specularStrength);
		}
	}
	Lighting() {}
	Lighting(Vector3 camPos, Program* p) {
		cameraPos = Vector3(camPos.x, camPos.y, camPos.z);
		cameraPos.uniformL = glGetUniformLocation(p->programId, "cameraPos");
		lightPos = Vector3(0, 5, 3);
		lightPos.uniformL = glGetUniformLocation(p->programId, "lightPos");
		lightColor = Vector3(1, 1, 1);
		lightColor.uniformL = glGetUniformLocation(p->programId, "lightColor");
		ambientStrengthLoc = glGetUniformLocation(p->programId, "ambientStrength");
		specularStrengthLoc = glGetUniformLocation(p->programId, "specularStrength");
	}
};