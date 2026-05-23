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
void Object3D::setup() {
	GLuint verticesSize = (GLuint) vertexBuffer.size() * sizeof(GLfloat);
	GLuint texCoordsSize = (GLuint) texBuffer.size() * sizeof(GLfloat);
	GLuint indicesSize = (GLuint) indexBuffer.size() * sizeof(GLuint);
	GLuint normalsSize = (GLuint) normalBuffer.size() * sizeof(GLfloat);
	b = renderUtils->createStaticVAO(vertexBuffer.data(), indexBuffer.data(), texBuffer.data(), normalBuffer.data(), verticesSize, indicesSize, texCoordsSize, normalsSize);
}
void Object3D::begin() {
	model.values = glm::mat4(1.0f);
	glBindVertexArray(b.VAO);
}
void Object3D::render() {
	model.uniform();
	glActiveTexture(texture->glType);
	glBindTexture(GL_TEXTURE_2D, texture->textureId);
	if (this->cam->autoUpdate) {
		this->cam->update();
	}
	if (cam->rendUtils->lighting != nullptr) {
		cam->rendUtils->lighting->bind();
	}
	if (texture->texSampleNum == -1) {
		std::cerr << "texture.texSampleNum is -1" << std::endl;
		return;
	}
	else {
		glUniform1i(texture->texSampleNum, texture->glType % GL_TEXTURE0);
	}
	glDrawElements(GL_TRIANGLES, (GLuint) indexBuffer.size(), GL_UNSIGNED_INT, 0);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error occured: 0x" << std::hex << err << std::dec << std::endl;
	}
}
void Object3D::end() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void Object3D::dispose() {
	end();
	glDeleteVertexArrays(1, &b.VAO);
	std::vector<GLuint> buffersToDelete;
	buffersToDelete.push_back(b.VBO);
	buffersToDelete.push_back(b.VBOtexture);
	buffersToDelete.push_back(b.EBO);
	if (cam->rendUtils->lighting != nullptr) buffersToDelete.push_back(b.VBOnormal);
	glDeleteBuffers((GLuint) buffersToDelete.size(), buffersToDelete.data());
	b = ObjectBuffer();
}