#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class OrtogonalProjection {
public:
	OrtogonalProjection(float left, float right, float bottom, float top);
	OrtogonalProjection(float left, float right, float bottom, float top, float zNear, float zFar);
	~OrtogonalProjection();

	glm::mat4& getMatrix();

private:
	glm::mat4 _matrix;
};

