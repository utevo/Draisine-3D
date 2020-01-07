#pragma once

#include <vector>
#include <memory>

#include "Object.h"


class CompositeObject : public Object {
public:
	virtual void render(std::shared_ptr<Shader> shader) override {
		for (Object& object : _objects)
			object.render(shader);
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

	virtual void rotate(const glm::vec3& vec) {
		for (Object& object : _objects)
			object.rotate(vec);
	}

	virtual void scale(const glm::vec3& vec) {
		for (Object& object : _objects)
			object.scale(vec);
	}

private:
	std::vector <Object&> _objects;
};