#include "Object3D.h"
Object3D::Object3D(Camera* camera, RenderUtils* rend, Texture* tex) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (rend == nullptr) {
		throw std::runtime_error("RenderUtils is null");
	}
	if (tex == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	this->cam = camera;
	renderUtils = rend;
	texture = tex;
	model = Matrix4(glGetUniformLocation(rend->p->programId, "model"));
}
void Object3D::begin() {
	renderUtils->bind(vertexBuffer, indexBuffer, texBuffer, vertBufSize, indexBufSize, texBufSize, normalBuffer, normalBufSize);
	model.values = glm::mat4(1.0f);
	glBindVertexArray(renderUtils->VAO);
}
void Object3D::render() {
	model.uniform();
	glActiveTexture(texture->glType);
	glBindTexture(GL_TEXTURE_2D, texture->textureId);
	if (this->cam->autoUpdate) {
		this->cam->update();
	}
	if (texture->texSampleNum == -1) {
		std::cerr << "texture.texSampleNum is -1" << std::endl;
		return;
	}
	else {
		glUniform1i(texture->texSampleNum, texture->glType % GL_TEXTURE0);
	}
	glDrawElements(GL_TRIANGLES, indexBufSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}
void Object3D::end() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Object3D::dispose() {
	end();
	free(vertexBuffer);
	free(indexBuffer);
	free(texBuffer);
	if (normalBuffer != nullptr) free(normalBuffer);
}