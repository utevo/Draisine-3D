#include "Textures.h"

#include <SOIL.h>
#include <GLFW/glfw3.h>

#include "Utilities.h"


Textures::Textures(std::vector <std::pair<unsigned int, Texture> > &mapping) {
	_mapping = mapping;
};


Textures::Textures(std::vector <Texture>& textures) {
	_mapping = std::vector <std::pair<unsigned int, Texture>>();
	
	for (unsigned int i = 0; i < textures.size(); ++i)
		_mapping.push_back({i, textures[i] });
}

Textures::~Textures() {
}

void Textures::bind() const {
	for (std::pair<unsigned int, Texture> pair : _mapping) {
		Texture& texture = pair.second;
		unsigned int slot = pair.first;
		texture.bind(slot);
	}
}

void Textures::unbind() const {
	for (std::pair<unsigned int, Texture> pair : _mapping) {
		Texture& texture = pair.second;
		unsigned int slot = pair.first;
		texture.unbind();
	}
}