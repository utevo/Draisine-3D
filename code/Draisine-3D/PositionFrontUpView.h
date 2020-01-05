#pragma once

#include <glm/glm.hpp>

#include "View.h"


class PositionFrontUpView : public View {
public:
	PositionFrontUpView(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	~PositionFrontUpView();

	glm::mat4& getMatrix();
	glm::vec3& getPosition() { return _position; }
	glm::vec3& getFront() { return _front; }
	glm::vec3& getUp() { return _up; }

private:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;

	glm::mat4 _matrix;
};