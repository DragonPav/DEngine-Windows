#include "ObjectCreator.h"
#include <vector>
Object3D ObjectCreator::createCustom(GLfloat* verts, GLuint* indxs, GLfloat* texCoords, GLfloat* normals, Camera* camera, Texture* texture) {
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
	ret.position = &pos;
	ret.vertexBuffer = (GLfloat*)malloc(sizeof(vertices));
	memcpy(ret.vertexBuffer, &vertices, sizeof(vertices));
	ret.indexBuffer = (GLuint*)malloc(sizeof(indices));
	memcpy(ret.indexBuffer, &indices, sizeof(indices));
	ret.texBuffer = (GLfloat*)malloc(sizeof(texCoords));
	memcpy(ret.texBuffer, &texCoords, sizeof(texCoords));
	if (camera->rendUtils->lighting != nullptr) {
		ret.normalBuffer = (GLfloat*)malloc(sizeof(normals));
		memcpy(ret.normalBuffer, &normals, sizeof(normals));
		ret.normalBufSize = sizeof(normals);
	}
	ret.vertBufSize = sizeof(vertices);
	ret.indexBufSize = sizeof(indices);
	ret.texBufSize = sizeof(texCoords);
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
	ret.position = &pos;
	ret.vertexBuffer = (GLfloat*)malloc(sizeof(vertices));
	memcpy(ret.vertexBuffer, &vertices, sizeof(vertices));
	ret.indexBuffer = (GLuint*)malloc(sizeof(indices));
	memcpy(ret.indexBuffer, &indices, sizeof(indices));
	ret.texBuffer = (GLfloat*)malloc(sizeof(texCoords));
	memcpy(ret.texBuffer, &texCoords, sizeof(texCoords));
	if (camera->rendUtils->lighting != nullptr) {
		ret.normalBuffer = (GLfloat*)malloc(sizeof(normals));
		memcpy(ret.normalBuffer, &normals, sizeof(normals));
		ret.normalBufSize = sizeof(normals);
	}
	ret.vertBufSize = sizeof(vertices);
	ret.indexBufSize = sizeof(indices);
	ret.texBufSize = sizeof(texCoords);
	return ret;
}
Object3D createSurface(Vector3 pos, Vector2 size, Camera* camera, Texture* tex) {
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
	ret.position = &pos;
	ret.vertexBuffer = (GLfloat*)malloc(sizeof(vertices));
	memcpy(ret.vertexBuffer, &vertices, sizeof(vertices));
	ret.indexBuffer = (GLuint*)malloc(sizeof(indices));
	memcpy(ret.indexBuffer, &indices, sizeof(indices));
	ret.texBuffer = (GLfloat*)malloc(sizeof(texCoords));
	memcpy(ret.texBuffer, &texCoords, sizeof(texCoords));
	if (camera->rendUtils->lighting != nullptr) {
		ret.normalBuffer = (GLfloat*)malloc(sizeof(normals));
		memcpy(ret.normalBuffer, &normals, sizeof(normals));
		ret.normalBufSize = sizeof(normals);
	}
	ret.vertBufSize = sizeof(vertices);
	ret.indexBufSize = sizeof(indices);
	ret.texBufSize = sizeof(texCoords);
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
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> texCoords;
	std::vector<float> normals;
	float x, y, z, xy;
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
			vertices.push_back(x + pos.x);
			vertices.push_back(y + pos.y);
			vertices.push_back(z + pos.z);
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			texCoords.push_back(s);
			texCoords.push_back(t);
		}
	}
	GLuint k1, k2;
	for (int i = 0; i < stackCount; i++) {
		k1 = i * (sectorCount + 1);
		k2 = k1 + sectorCount + 1;
		for (int j = 0; j < sectorCount; j++, k1++, k2++) {
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
			if (i != (stackCount - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
	ret.position = &pos;
	ret.vertexBuffer = (GLfloat*)malloc(sizeof(GLfloat) * vertices.size());
	std::copy(vertices.begin(), vertices.end(), ret.vertexBuffer);
	ret.indexBuffer = (GLuint*)malloc(sizeof(GLuint) * indices.size());
	std::copy(indices.begin(), indices.end(), ret.indexBuffer);
	ret.texBuffer = (GLfloat*)malloc(sizeof(GLfloat) * texCoords.size());
	std::copy(texCoords.begin(), texCoords.end(), ret.texBuffer);
	if (camera->rendUtils->lighting != nullptr) {
		ret.normalBuffer = (GLfloat*)malloc(sizeof(GLfloat) * normals.size());
		std::copy(normals.begin(), normals.end(), ret.normalBuffer);
		ret.normalBufSize = sizeof(GLfloat) * (GLuint) normals.size();
	}
	ret.vertBufSize = (GLuint) sizeof(GLfloat) * (GLuint) vertices.size();
	ret.indexBufSize = (GLuint) sizeof(GLuint) * (GLuint) indices.size();
	ret.texBufSize = (GLuint) sizeof(GLfloat) * (GLuint) texCoords.size();
	normals.clear();
	vertices.clear();
	indices.clear();
	texCoords.clear();
	return ret;
}