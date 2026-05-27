#include "ObjectCreator.h"
#include <vector>
Object3D ObjectCreator::createCustom(std::vector<GLfloat> verts, std::vector<GLuint> indxs, std::vector<GLfloat> texCoords, std::vector<GLfloat> normals, Camera* camera, Texture* texture) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (texture == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	Object3D ret(camera, camera->rendUtils, texture);
	ret.vertexBuffer = verts;
	ret.indexBuffer = indxs;
	ret.texBuffer = texCoords;
	ret.normalBuffer = normals;
	ret.setup();
	return ret;
}
Object3D ObjectCreator::createBox(Vector3 pos, Vector3 size, Camera* camera, Texture* texture) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (texture == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	Object3D ret(camera, camera->rendUtils, texture);
	GLfloat halfWidth = size.x / 2;
	GLfloat halfHeight = size.y / 2;
	GLfloat halfDepth = size.z / 2;
	GLfloat vertices[] = {
		//back
		pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		//left
		pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		//front
		pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		//right
		pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		//top
		pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		//bottom
		pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth
	};
	GLuint indices[] = {
		//back
		0, 1, 2,
		2, 3, 1,
		//left
		4, 5, 6,
		6, 7, 5,
		//front
		8, 9, 10,
		10, 11, 9,
		//right
		12, 13, 14,
		14, 15, 13,
		//top
		16, 17, 18,
		18, 19, 17,
		//bottom
		20, 21, 22,
		22, 23, 21
	};
	GLfloat texCoords[] = {
		//back
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//left
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//front
		1, 1,
		0, 1,
		1, 0,
		0, 0,
		//right
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//top
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//bottom
		1, 1,
		0, 1,
		1, 0,
		0, 0
	};
	GLfloat normals[] = {
		//back
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		//left
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		//front
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		//right
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		//top
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		//bottom
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0
	};
	ret.position = pos;
	Vector3 min(pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth);
	Vector3 max(pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth);
	ret.bounds = BoundingBox(min, max);
	for (int i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
		ret.vertexBuffer.push_back(vertices[i]);
	}
	for (int i = 0; i < sizeof(indices) / sizeof(GLuint); i++) {
		ret.indexBuffer.push_back(indices[i]);
	}
	for (int i = 0; i < sizeof(texCoords) / sizeof(GLfloat); i++) {
		ret.texBuffer.push_back(texCoords[i]);
	}
	if (camera->rendUtils->lighting != nullptr) {
		for (int i = 0; i < sizeof(normals) / sizeof(GLfloat); i++) {
			ret.normalBuffer.push_back(normals[i]);
		}
	}
	ret.setup();
	return ret;
}
Object3D ObjectCreator::createQuad(Vector3 pos, Vector2 size, Camera* camera, Texture* tex) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (tex == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	Object3D ret(camera, camera->rendUtils, tex);
	float halfWidth = size.x / 2;
	float halfHeight = size.y / 2;
	GLfloat vertices[] = {
		pos.x - halfWidth, pos.y - halfHeight, pos.z,
		pos.x + halfWidth, pos.y - halfHeight, pos.z,
		pos.x - halfWidth, pos.y + halfHeight, pos.z,
		pos.x + halfWidth, pos.y + halfHeight, pos.z
	};
	GLuint indices[] = {
		0, 1, 2,
		2, 3, 1
	};
	GLfloat texCoords[] = {
		0, 1,
		1, 1,
		0, 0,
		1, 0
	};
	GLfloat normals[] = {
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1
	};
	ret.position = pos;
	Vector3 min(pos.x - halfWidth, pos.y - halfHeight, pos.z);
	Vector3 max(pos.x + halfWidth, pos.y + halfHeight, pos.z);
	ret.bounds = BoundingBox(min, max);
	for (size_t i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
		ret.vertexBuffer.push_back(vertices[i]);
	}
	for (size_t i = 0; i < sizeof(indices) / sizeof(GLuint); i++) {
		ret.indexBuffer.push_back(indices[i]);
	}
	for (size_t i = 0; i < sizeof(texCoords) / sizeof(GLfloat); i++) {
		ret.texBuffer.push_back(texCoords[i]);
	}
	if (camera->rendUtils->lighting != nullptr) {
		for (size_t i = 0; i < sizeof(normals) / sizeof(GLfloat); i++) {
			ret.normalBuffer.push_back(normals[i]);
		}
	}
	ret.setup();
	return ret;
}
Object3D ObjectCreator::createSurface(Vector3 pos, Vector2 size, Camera* camera, Texture* tex) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (tex == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	Object3D ret(camera, camera->rendUtils, tex);
	GLfloat halfWidth = size.x / 2;
	GLfloat halfDepth = size.y / 2;
	GLfloat vertices[] = {
		pos.x - halfWidth, pos.y, pos.z + halfDepth,
		pos.x + halfWidth, pos.y, pos.z + halfDepth,
		pos.x - halfWidth, pos.y, pos.z - halfDepth,
		pos.x + halfWidth, pos.y, pos.z - halfDepth
	};
	GLuint indices[] = {
		0, 1, 2,
		2, 3, 1
	};
	GLfloat texCoords[] = {
		0, 1,
		1, 1,
		0, 0,
		1, 0
	};
	GLfloat normals[] = {
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};
	ret.position = pos;
	Vector3 min(pos.x - halfWidth, pos.y, pos.z - halfDepth);
	Vector3 max(pos.x + halfWidth, pos.y, pos.z + halfDepth);
	ret.bounds = BoundingBox(min, max);
	for (size_t i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
		ret.vertexBuffer.push_back(vertices[i]);
	}
	for (size_t i = 0; i < sizeof(indices) / sizeof(GLuint); i++) {
		ret.indexBuffer.push_back(indices[i]);
	}
	for (size_t i = 0; i < sizeof(texCoords) / sizeof(GLfloat); i++) {
		ret.texBuffer.push_back(texCoords[i]);
	}
	if (camera->rendUtils->lighting != nullptr) {
		for (size_t i = 0; i < sizeof(normals) / sizeof(GLfloat); i++) {
			ret.normalBuffer.push_back(normals[i]);
		}
	}
	ret.setup();
	return ret;
}
Object3D ObjectCreator::createSphere(Vector3 pos, float radius, int sectorCount, int stackCount, Camera* camera, Texture* tex) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (tex == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	Object3D ret(camera, camera->rendUtils, tex);
	float x = 0, y = 0, z = 0, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	float s, t;

	float sectorStep = 2 * 3.14159f / sectorCount;
	float stackStep = 3.14159f / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; i++) {
		stackAngle = (float)3.14159 / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);
		for (int j = 0; j <= sectorCount; j++) {
			sectorAngle = j * sectorStep;
			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			ret.vertexBuffer.push_back(x + pos.x);
			ret.vertexBuffer.push_back(y + pos.y);
			ret.vertexBuffer.push_back(z + pos.z);
			if (ret.renderUtils->lighting != nullptr) {
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				ret.normalBuffer.push_back(nx);
				ret.normalBuffer.push_back(ny);
				ret.normalBuffer.push_back(nz);
			}
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			ret.texBuffer.push_back(s);
			ret.texBuffer.push_back(t);
		}
	}
	GLuint k1, k2;
	for (int i = 0; i < stackCount; i++) {
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;
		for (int j = 0; j < sectorCount; j++, k1++, k2++) {
			if (i != 0) {
				ret.indexBuffer.push_back(k1);
				ret.indexBuffer.push_back(k2);
				ret.indexBuffer.push_back(k1 + 1);
			}
			if (i != (stackCount - 1)) {
				ret.indexBuffer.push_back(k1 + 1);
				ret.indexBuffer.push_back(k2);
				ret.indexBuffer.push_back(k2 + 1);
			}
		}
	}
	ret.bounds = BoundingBox(
		Vector3(pos.x - radius, pos.y - radius, pos.z - radius),
		Vector3(pos.x + radius, pos.y + radius, pos.z + radius)
	);
	ret.position = pos;
	ret.setup();
	return ret;
}
Object3D ObjectCreator::createBoxWireframe(Vector3 pos, Vector3 size, Camera* camera, Texture* texture) {
	if (camera == nullptr) {
		throw std::runtime_error("Camera is null");
	}
	if (texture == nullptr) {
		throw std::runtime_error("Texture is null");
	}
	Object3D ret(camera, camera->rendUtils, texture);
	GLfloat halfWidth = size.x / 2;
	GLfloat halfHeight = size.y / 2;
	GLfloat halfDepth = size.z / 2;
	GLfloat vertices[] = {
		//back
		pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		//left
		pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		//front
		pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		//right
		pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		//top
		pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth,
		//bottom
		pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth,
		pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth,
		pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth
	};
	GLuint indices[] = {
		//back
		0, 1,
		1, 2,
		2, 0,
		2, 3,
		//left
		4, 5,
		5, 6,
		6, 4,
		6, 7,
		//front
		8, 9,
		9, 10,
		10, 8,
		10, 11,
		//right
		12, 13,
		13, 14,
		14, 12,
		14, 15,
		//top
		16, 17,
		17, 18,
		18, 16,
		18, 19,
		//bottom
		20, 21,
		21, 22,
		22, 20,
		22, 23
	};
	GLfloat texCoords[] = {
		//back
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//left
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//front
		1, 1,
		0, 1,
		1, 0,
		0, 0,
		//right
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//top
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		//bottom
		1, 1,
		0, 1,
		1, 0,
		0, 0
	};
	GLfloat normals[] = {
		//back
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		//left
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		//front
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		//right
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		//top
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		//bottom
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0
	};
	ret.position = pos;
	Vector3 min(pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth);
	Vector3 max(pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth);
	ret.bounds = BoundingBox(min, max);
	ret.polygonMode = GL_LINES;
	for (int i = 0; i < sizeof(vertices) / sizeof(GLfloat); i++) {
		ret.vertexBuffer.push_back(vertices[i]);
	}
	for (int i = 0; i < sizeof(indices) / sizeof(GLuint); i++) {
		ret.indexBuffer.push_back(indices[i]);
	}
	for (int i = 0; i < sizeof(texCoords) / sizeof(GLfloat); i++) {
		ret.texBuffer.push_back(texCoords[i]);
	}
	if (camera->rendUtils->lighting != nullptr) {
		for (int i = 0; i < sizeof(normals) / sizeof(GLfloat); i++) {
			ret.normalBuffer.push_back(normals[i]);
		}
	}
	ret.setup();
	return ret;
}