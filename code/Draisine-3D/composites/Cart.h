#pragma once

#include "../CompositeObject.h"
#include "../primitives/Cube.h"
#include "Wheels.h"
#include<iostream>

class Cart : public CompositeObject {
public:
	Cart(const glm::vec3& possition = { 0.0, 0.0, 0.0 },
		const glm::vec3& rotation = { 0.0, 0.0, 0.0 },
		const glm::vec3& size = { 1.0f, 1.0f, 1.0f }): speed(0) {
		auto cart_tex = std::make_shared<Texture>("textures/cart.png");
		auto wh = std::make_unique<Wheels>(possition + glm::vec3(0.0, -0.22, 0.0), rotation, size);
		auto bs = std::make_unique<Cube>(cart_tex, possition + glm::vec3(0.0, -0.22, 0.0), rotation, size * glm::vec3(0.5, 0.02, 1.0));
		wheels = wh.get();
		base = bs.get();
		addChild(std::move(bs));
		addChild(std::move(wh));
	}

	void addSpeed(float step)
	{
		speed += step;
		std::cout << speed << std::endl;
		if (speed >  15) speed =  15;
		if (speed < -15) speed = -15;
	}

	void moveAuto()
	{
		move(speed * glm::vec3(0.0, 0.0, 0.004));
		rotateWheels(speed * glm::vec3(0.0, 0.0, 1.0));
	}

	void rotateWheels(const glm::vec3& rotation) {
		wheels->rotate(rotation);
	}

	glm::vec3 getPos()
	{
		return base->getPos();
	}

private:
	Wheels* wheels;
	Cube* base;
	float speed;
};

