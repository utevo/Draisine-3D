#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class PerspectiveProjection {
public:
	PerspectiveProjection(float fovy, float aspect, float near, float far);
	~PerspectiveProjection();

	glm::mat4& getMatrix();

private:
	glm::mat4 _matrix;
};

