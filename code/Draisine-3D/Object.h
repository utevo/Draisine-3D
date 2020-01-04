#pragma once

#include "Renderer.h"

class Object {
public:
	Object() {};
	//virtual ~Object() = 0;
	virtual void render(Renderer& renderer) = 0;
};

