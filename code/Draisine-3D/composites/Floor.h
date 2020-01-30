#pragma once

#include "../CompositeObject.h"
#include "../primitives/Ground.h"
#include "railway.h"
#include<iostream>

class Floor : public CompositeObject {
public:
	Floor(int number = 1, const glm::vec3& possition = { 0.0, 0.0, 0.0 },
		const glm::vec3& rotation = { 0.0, 0.0, 0.0 },
		const glm::vec3& size = { 1.0f, 1.0f, 1.0f }) {
		auto ground_tex = std::make_shared<Texture>("textures/cracked_ground.png", true);
		auto bs = std::make_unique<Ground>(ground_tex, possition, rotation, size);
		auto rw = std::make_unique<Railway>(6 + 10 * number);
		center = bs.get();
		railway = rw.get();
		addChild(std::move(rw));
		addChild(std::move(bs));
		for (int i = 1; i <= number; ++i)
		{
			addChild(std::move(std::make_unique<Ground>(ground_tex, possition + i*offset, rotation, size)));
			addChild(std::move(std::make_unique<Ground>(ground_tex, possition - i*offset, rotation, size)));
		}
	}

	void reposition(int dir)
	{
		if (dir > 0)
			move(offset);
		else
			move(-offset);
	}

	glm::vec3 getPos()
	{
		return center->getPos();
	}

	void renderRailway(std::shared_ptr<Shader> shader, bool tex = true)
	{
		railway->render(shader, tex);
	}

private:
	Ground* center;
	Railway* railway;
	const glm::vec3 offset = {0.0, 0.0, 10.0};

};

