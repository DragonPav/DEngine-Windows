#pragma once
#include <vector>
#include "Texture.h"
#include "Camera.h"
#include "ObjectBuffer.h"
class Camera;
class RenderUtils;
class Object3D {
public:
	Vector3 position;
	Matrix4 model;
	std::vector<GLfloat> vertexBuffer;
	std::vector<GLuint> indexBuffer;
	std::vector<GLfloat> texBuffer;
	std::vector<GLfloat> normalBuffer;
	Texture* texture;
	ObjectBuffer b;
	Camera* cam = nullptr;
	RenderUtils* renderUtils = nullptr;
	void setup();
	void begin();
	void render();
	void end();
	void dispose();
	Object3D() = delete;
	Object3D(Camera* camera, RenderUtils* rend, Texture* tex);
};