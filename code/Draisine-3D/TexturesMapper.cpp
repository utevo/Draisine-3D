#include "TexturesMapper.h"

#include <SOIL.h>
#include <GLFW/glfw3.h>

#include "Utilities.h"


TexturesMapper::TexturesMapper() : _mapping(std::vector <std::pair<std::string, Texture&> >()), _shader(Shader()) {
};

TexturesMapper::TexturesMapper(std::vector <std::pair<std::string, Texture&> > &mapping, Shader& shader)
: _shader(shader), _mapping(mapping) {
};

TexturesMapper::~TexturesMapper() {
}

void TexturesMapper::bind() const {
	unsigned int slot = 0;
	for (std::pair<std::string, Texture&> &pair : _mapping) {
		Texture& texture = pair.second;
		std::string name = pair.first;
		texture.bind(slot);
		_shader.setUniformInt(name, slot);
		++slot;
	}
}

void TexturesMapper::unbind() const {
	for (std::pair<std::string, Texture&> &pair : _mapping) {
		Texture& texture = pair.second;
		std::string name = pair.first;
		texture.unbind();
	}
}