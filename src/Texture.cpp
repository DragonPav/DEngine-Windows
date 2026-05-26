#include "Texture.h"
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"
Texture::Texture(std::vector<GLubyte> rgb, Program* p, Config cfg) {
	texSampleNum = glGetUniformLocation(p->programId, "textureUnit");
	int i = 0;
	while (i < 256 * 256 * 3) {
		colorBuffer.push_back(rgb[0]);
		i++;
		colorBuffer.push_back(rgb[1]);
		i++;
		colorBuffer.push_back(rgb[2]);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, colorBuffer.data());
	if (cfg.useMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::Texture(Program* p, std::string file, Config cfg) {
	texSampleNum = glGetUniformLocation(p->programId, "textureUnit");
	int width, height, bpp;
	unsigned char* dat = stbi_load(file.c_str(), &width, &height, &bpp, 0);
	size_t size = static_cast<size_t>(width) * height * bpp;
	colorBuffer.insert(colorBuffer.begin(), dat, dat + size);
	if (stbi_failure_reason()) {
		std::cerr << "STBI error: " << stbi_failure_reason() << std::endl;
		return;
	}
	GLuint tmpBuf[1];
	glGenTextures(1, tmpBuf);
	textureId = tmpBuf[0];
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, cfg.textureWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, cfg.textureWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, cfg.textureMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, cfg.textureMagFilter);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, colorBuffer.data());
	if (glGetError() != GL_NO_ERROR) {
		std::cerr << "Texture setup failure: gl error: " << glGetError() << std::endl;
	}
	if (cfg.useMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(dat);
}
void Texture::dispose() {
	glDeleteTextures(1, &textureId);
}