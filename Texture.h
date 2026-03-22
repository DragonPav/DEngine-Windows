#pragma once
#include "Program.h"
class Texture {
public:
	class Config {
	public:
		bool useMipmap = true;
		int textureWrapS = GL_CLAMP_TO_EDGE;
		int textureWrapT = GL_CLAMP_TO_EDGE;
		int textureMinFilter = GL_NEAREST_MIPMAP_LINEAR;
		int textureMagFilter = GL_NEAREST;
		Config() = default;
	};
	GLint texSampleNum = 0;
	GLuint textureId = 0;
	GLubyte* colorBuffer;
	int glType = GL_TEXTURE0;
	void dispose();
	Texture(GLubyte(&rgb)[3], Program* p, Config cfg);
	Texture() = delete;
};