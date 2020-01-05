#pragma once

#include <vector>

#include "Object.h"


class CompositeObject : public Object {
public:
	virtual void render() {
		for (Object& object : _objects)
			object.render();
	}

	void add(Object& object) {
		_objects.push_back(object);
	}

private:
	std::vector <Object&> _objects;
};