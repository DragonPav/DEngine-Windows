#pragma once
#include "Texture.h"
#include "Camera.h"
class Camera;
class RenderUtils;
class Object3D {
public:
	Vector3* position = nullptr;
	Matrix4 model;
	GLfloat* vertexBuffer{};
	GLuint* indexBuffer{};
	GLfloat* texBuffer{};
	GLfloat* normalBuffer{};
	Texture* texture;
	GLuint vertBufSize = 0, indexBufSize = 0, texBufSize = 0, normalBufSize = 0;
	Camera* cam = nullptr;
	RenderUtils* renderUtils = nullptr;
	void begin();
	void render();
	void end();
	void dispose();
	Object3D() = delete;
	Object3D(Camera* camera, RenderUtils* rend, Texture* tex);
};