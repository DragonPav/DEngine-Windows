#include "Texture.h"
Texture::Texture(GLubyte(&rgb)[3], Program* p, Config cfg) {
	texSampleNum = glGetUniformLocation(p->programId, "textureUnit");
	colorBuffer = (GLubyte*)malloc(sizeof(GLubyte) * 256 * 256 * 3);
	int i = 0;
	while (i < 256 * 256 * 3) {
		colorBuffer[i] = rgb[0];
		i++;
		colorBuffer[i] = rgb[1];
		i++;
		colorBuffer[i] = rgb[2];
		i++;
	}
	GLuint tmpBuf[1];
	glGenTextures(1, tmpBuf);
	textureId = tmpBuf[0];
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cfg.textureWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cfg.textureWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, cfg.textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, cfg.textureMagFilter);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, colorBuffer);
	if (cfg.useMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::dispose() {
	glDeleteTextures(1, &textureId);
	free(colorBuffer);
}