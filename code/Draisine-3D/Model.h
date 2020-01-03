#pragma once

#include <glm/glm.hpp>

class Model {
public:
	Model(glm::mat4& matrix) : _matrix(matrix) {}
	~Model() {}

	glm::mat4& getMatrix() { return _matrix;  }
	void setMatrix(glm::mat4 matrix) { _matrix = matrix; }

private:
	glm::mat4 _matrix;
};