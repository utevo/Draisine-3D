#pragma once

#include <vector>

#include "Object.h"


class CompositeObject : public Object {
public:
	virtual void render(Renderer& renderer) {
		for (Object& object : _objects)
			object.render(renderer);
	}

	void addChild(Object& object) {
		_objects.push_back(object);
	}
	void removeChild(unsigned int number) {
		_objects.erase(_objects.begin() + number);
	}

	virtual void move(const glm::vec3& vec) {
		for (Object& object : _objects)
			object.move(vec);
	}
	virtual void scale(const glm::vec3& vec) {
		for (Object& object : _objects)
			object.scale(vec);
	}
	virtual void rotate(const glm::vec3& vec) {
		for (Object& object : _objects)
			object.rotate(vec);
	}
private:
	std::vector <Object&> _objects;
};