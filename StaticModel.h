#pragma once
#include "Object3D.h"
class StaticModel {
public:
    Matrix4 model;
    GLfloat* vertexBuffer{};
	GLuint* indexBuffer{};
	GLfloat* texBuffer{};
	GLfloat* normalBuffer{};
    Texture* texture;
    GLuint vertBufSize = 0, indexBufSize = 0, texBufSize = 0, normalBufSize = 0;
	unsigned int* offsets;
	Camera* cam = nullptr;
	RenderUtils* renderUtils = nullptr;
    void begin();
	void render();
	void end();
	void dispose();
	StaticModel() = delete;
	StaticModel(Camera* camera, RenderUtils* rend, Object3D* objs[], unsigned int count);
};