#pragma once

#include "../CompositeObject.h"
#include "../primitives/Cylinder.h"
#include "../primitives/Sphere.h"
#include <stdlib.h>
#include <time.h>  

#define MAX_BRANCHES 4
#define MAX_STEM_HEIGHT 10
#define STEM_OFFSET 6
#define BRANCH_OFFSET 2
class Cactus : public CompositeObject {
public:
	Cactus(const glm::vec3& possition = { 2.0, -0.51, 0.0 },
		const glm::vec3& rotation = { -90.0f, 0.0f, -90.0f },
		const glm::vec3& size = { 0.1f, 0.1f, 0.1f }) {
		srand(time(NULL));
		glm::vec3 stem_size(size);
		glm::vec3 height_unit = { 0.0f,0.1f,0.0f };
		glm::vec3 branch_offset_horizontal = { 0.2f,0.0f,0.0f };
		auto cacti_tex = std::make_shared<Texture>("textures/cacti_tex.png");
		int branch_nr = rand() % (MAX_BRANCHES-2 )+2;
		int stem_height = rand() % (MAX_STEM_HEIGHT+1-STEM_OFFSET) + STEM_OFFSET; //

		stem_size[2] *= stem_height;
		auto stem = std::make_unique<Cylinder>(cacti_tex, possition, rotation, stem_size);
		glm::vec3 top_position(possition);
		top_position[1] += stem_size[2];
		auto stem_top = std::make_unique<Sphere>(cacti_tex, top_position, rotation, size);
		addChild(std::move(stem));
		addChild(std::move(stem_top));
		float branch_revolution = 360.0f/branch_nr;
		if (branch_nr != 0)branch_revolution /= branch_nr;
		glm::mat4 rotationMat(1);
		rotationMat = glm::rotate(rotationMat, branch_revolution, glm::vec3(0.0, 1.0, 0.0));

		int lower_bound = 0;
		int upper_bound = 0;
		for(int i=0;i<branch_nr;i++) {
			branch_offset_horizontal = glm::vec3(rotationMat * glm::vec4(branch_offset_horizontal, 1.0));

		    lower_bound = rand() % (stem_height - BRANCH_OFFSET) + BRANCH_OFFSET;
		    upper_bound = 0;
			while(upper_bound<=lower_bound)upper_bound=rand() % (stem_height - BRANCH_OFFSET) + BRANCH_OFFSET;
			glm::vec3 branch_size(size);
			branch_size[2] *= (upper_bound - lower_bound);
			
			auto branch_top = std::make_unique<Sphere>(cacti_tex, possition + branch_offset_horizontal + (height_unit * upper_bound), rotation, size);

			auto branch_bottom = std::make_unique<Sphere>(cacti_tex, possition + branch_offset_horizontal + (height_unit * lower_bound), rotation, size);
			
			
			auto branch = std::make_unique<Cylinder>(cacti_tex, possition + branch_offset_horizontal+(height_unit*lower_bound), rotation, branch_size);
			
			addChild(std::move(branch));
			addChild(std::move(branch_top));
			addChild(std::move(branch_bottom));
		  
		
		}
	}

	

	
	/*glm::vec3 getPos()
	{
		return base->getPos();
	}
	*/
private:
	
};

