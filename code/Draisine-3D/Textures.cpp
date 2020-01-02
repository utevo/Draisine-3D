#include "Textures.h"

#include <SOIL.h>
#include <GLFW/glfw3.h>

#include "Utilities.h"


TexturesMapper::TexturesMapper(std::vector <std::pair<unsigned int, Texture> > &mapping) {
	_mapping = mapping;
};


TexturesMapper::TexturesMapper(std::vector <Texture>& textures) {
	_mapping = std::vector <std::pair<unsigned int, Texture>>();
	
	for (unsigned int i = 0; i < textures.size(); ++i)
		_mapping.push_back({i, textures[i] });
}

TexturesMapper::~TexturesMapper() {
}

void TexturesMapper::bind() const {
	for (std::pair<unsigned int, Texture> pair : _mapping) {
		Texture& texture = pair.second;
		unsigned int slot = pair.first;
		texture.bind(slot);
	}
}

void TexturesMapper::unbind() const {
	for (std::pair<unsigned int, Texture> pair : _mapping) {
		Texture& texture = pair.second;
		unsigned int slot = pair.first;
		texture.unbind();
	}
}