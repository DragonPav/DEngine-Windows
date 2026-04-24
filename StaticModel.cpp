#include "StaticModel.h"
StaticModel::StaticModel(Camera* camera, RenderUtils* rend, Object3D* objs[], unsigned int count) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (rend == nullptr) {
		throw std::runtime_error("RenderUtils is null");
	}
	if (objs == nullptr) {
		throw std::runtime_error("Objects is null");
	}
	this->cam = camera;
	renderUtils = rend;
	for (unsigned int i = 0; i < count; i++) {
		vertBufSize += objs[i]->vertBufSize;
		indexBufSize += objs[i]->indexBufSize;
		texBufSize += objs[i]->texBufSize;
		if (objs[i]->renderUtils->lighting != nullptr) normalBufSize += objs[i]->normalBufSize;
	}
	vertexBuffer = (GLfloat*)malloc(vertBufSize);
	indexBuffer = (GLuint*)malloc(indexBufSize);
	texBuffer = (GLfloat*)malloc(texBufSize);
	if (objs[0]->renderUtils->lighting != nullptr) normalBuffer = (GLfloat*)malloc(normalBufSize);
	unsigned int vertexOffset = 0;
	unsigned int lastV = 0, lastI = 0, lastT = 0, lastN = 0;
	texture = objs[0]->texture;
	for (unsigned int i = 0; i < count; i++) {
		memcpy((char*)vertexBuffer + lastV, objs[i]->vertexBuffer, objs[i]->vertBufSize);
		lastV += objs[i]->vertBufSize;
		unsigned int indexCount = objs[i]->indexBufSize / sizeof(GLuint);
		for (unsigned int j = 0; j < indexCount; j++) {
			indexBuffer[lastI / sizeof(GLuint) + j] = objs[i]->indexBuffer[j] + vertexOffset;
		}
		vertexOffset += objs[i]->vertBufSize / (sizeof(GLfloat) * 3);
		memcpy((char*)texBuffer + lastT, objs[i]->texBuffer, objs[i]->texBufSize);
		lastI += objs[i]->indexBufSize;
		lastT += objs[i]->texBufSize;
		if (objs[i]->renderUtils->lighting != nullptr) {
			memcpy((char*)normalBuffer + lastN, objs[i]->normalBuffer, objs[i]->normalBufSize);
			lastN += objs[i]->normalBufSize;
		}
	}
	model = Matrix4(glGetUniformLocation(rend->p->programId, "model"));
}
void StaticModel::begin() {
	renderUtils->bind(vertexBuffer, indexBuffer, texBuffer, vertBufSize, indexBufSize, texBufSize, normalBuffer, normalBufSize);
	model.values = glm::mat4(1.0f);
	glBindVertexArray(renderUtils->VAO);
}
void StaticModel::render() {
	model.uniform();
	glActiveTexture(texture->glType);
	glBindTexture(GL_TEXTURE_2D, texture->textureId);
	if (texture->texSampleNum == -1) {
		std::cerr << "texture.texSampleNum is -1" << std::endl;
		return;
	}
	else {
		glUniform1i(texture->texSampleNum, texture->glType % GL_TEXTURE0);
	}
	glDrawElements(GL_TRIANGLES, indexBufSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
void StaticModel::end() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void StaticModel::dispose() {
	end();
	free(vertexBuffer);
	free(indexBuffer);
	free(texBuffer);
	if (normalBuffer != nullptr) free(normalBuffer);
}