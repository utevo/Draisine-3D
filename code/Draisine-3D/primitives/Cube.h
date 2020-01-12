#pragma once

#include "../PrimitiveObject.h"


class Cube : public PrimitiveObject {
public:
	Cube(std::shared_ptr<Texture> texture,
		const glm::vec3& possition = { 0.0, 0.0, 0.0 },
		const glm::vec3& rotation = { 0.0, 0.0, 0.0 },
		const glm::vec3& size = { 1.0f, 1.0f, 1.0f })
		: PrimitiveObject(texture, possition, rotation, size) {
		init();
	}

	std::unique_ptr<VertexBuffer> initVertexBuffer() override {
		GLfloat vertices[] = {
			// coordinates			// normals				// texture
			-1.0f,	-1.0f,	 1.0f,	-1.0f,	-1.0f,	 1.0f,	1.0f,	1.0f,
			 1.0f,	-1.0f,	 1.0f,	 1.0f,	-1.0f,	 1.0f,	0.25f,	1.0f,
			 1.0f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	 1.0f,	0.5f,	1.0f,
			-1.0f,	 1.0f,	 1.0f,	-1.0f,	 1.0f,	 1.0f,	0.75f,	1.0f,
			-1.0f,	-1.0f,	-1.0f,  -1.0f,	-1.0f,	-1.0f,	1.0f,	0.0f,
			 1.0f,	-1.0f,	-1.0f,	 1.0f,	-1.0f,	-1.0f,	0.25f,	0.0f,
			 1.0f,	 1.0f,	-1.0f,	 1.0f,	 1.0f,	-1.0f,	0.5f,	0.0f,
			-1.0f,	 1.0f,	-1.0f,	-1.0f,	 1.0f,	-1.0f,	0.75f,	0.0f

		};

		auto vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		return vertexBuffer;
	}

	std::unique_ptr<IndexBuffer> initIndexBuffer() override {
		GLuint indices[] = {
			// front
				0, 1, 2,
				2, 3, 0,
				// right
				1, 5, 6,
				6, 2, 1,
				// back
				7, 6, 5,
				5, 4, 7,
				// left
				4, 0, 3,
				3, 7, 4,
				// bottom
				4, 5, 1,
				1, 0, 4,
				// top
				3, 2, 6,
				6, 7, 3
		};

		auto indexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));
		return indexBuffer;
	}
};