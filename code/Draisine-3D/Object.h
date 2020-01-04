#pragma once

#include "Renderer.h"

class Object {
public:
	virtual void render(Renderer& renderer) = 0;
};

