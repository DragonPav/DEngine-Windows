#include "Lighting.h"
#include <string>
#include <vector>
DirLight::DirLight(Program* p) {
	this->p = p;
	ambient = Vector3(0.1f, 0.1f, 0.1f);
	ambient.uniformL = glGetUniformLocation(p->programId, "dirLight.ambient");
	diffuse = Vector3(0.6f, 0.6f, 0.6f);
	diffuse.uniformL = glGetUniformLocation(p->programId, "dirLight.diffuse");
	specular = Vector3(1, 1, 1);
	specular.uniformL = glGetUniformLocation(p->programId, "dirLight.specular");
	direction = Vector3(0, -2, -2);
	direction.uniformL = glGetUniformLocation(p->programId, "dirLight.direction");
}
void DirLight::bind() {
	ambient.uniform();
	diffuse.uniform();
	specular.uniform();
	direction.uniform();
	if (constantLoc != -1) {
		glUniform1f(constantLoc, constant);
	}
	if (linearLoc != -1) {
		glUniform1f(linearLoc, linear);
	}
	if (quadraticLoc != -1) {
		glUniform1f(quadraticLoc, quadratic);
	}
}
PointLight::PointLight(Program* p, GLint number) {
	this->p = p;
	ambient = Vector3(0.1f, 0.1f, 0.1f);
	std::string ambientS = "pointLights[" + std::to_string(number) + "].ambient";
	ambient.uniformL = glGetUniformLocation(p->programId, ambientS.c_str());
	diffuse = Vector3(0.6f, 0.6f, 0.6f);
	std::string diffuseS = "pointLights[" + std::to_string(number) + "].diffuse";
	diffuse.uniformL = glGetUniformLocation(p->programId, diffuseS.c_str());
	specular = Vector3(1, 1, 1);
	std::string specularS = "pointLights[" + std::to_string(number) + "].specular";
	specular.uniformL = glGetUniformLocation(p->programId, specularS.c_str());
	position = Vector3(0, 2, 0);
	std::string positionS = "pointLights[" + std::to_string(number) + "].position";
	position.uniformL = glGetUniformLocation(p->programId, positionS.c_str());
	std::string constantS = "pointLights[" + std::to_string(number) + "].constant";
	constantLoc = glGetUniformLocation(p->programId, constantS.c_str());
	std::string linearS = "pointLights[" + std::to_string(number) + "].linear";
	linearLoc = glGetUniformLocation(p->programId, linearS.c_str());
	std::string quadraticS = "pointLights[" + std::to_string(number) + "].quadratic";
	quadraticLoc = glGetUniformLocation(p->programId, quadraticS.c_str());
}
void PointLight::bind() {
	ambient.uniform();
	diffuse.uniform();
	specular.uniform();
	position.uniform();
	if (constantLoc != -1) {
		glUniform1f(constantLoc, constant);
	}
	if (linearLoc != -1) {
		glUniform1f(linearLoc, linear);
	}
	if (quadraticLoc != -1) {
		glUniform1f(quadraticLoc, quadratic);
	}
}
Lighting::Lighting(Vector3 camPos, Program* p) {
	cameraPos = Vector3(camPos.x, camPos.y, camPos.z);
	cameraPos.uniformL = glGetUniformLocation(p->programId, "cameraPos");
	DirLight dir(p);
	dirLight = &dir;
	pointLights.push_back(PointLight(p, 0));
}
void Lighting::bind() {
	cameraPos.uniform();
	dirLight->bind();
	for (PointLight pointLight : pointLights) {
		pointLight.bind();
	}
}