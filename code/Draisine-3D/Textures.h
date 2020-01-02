#pragma once

#include <vector>
#include <utility>

#include "Utilities.h"
#include "Texture.h"


class TexturesMapper {
public:
    TexturesMapper(std::vector <std::pair<unsigned int, Texture> > &mapping);
    TexturesMapper(std::vector <Texture> &textures);
    ~TexturesMapper();

    void bind() const;
    void unbind() const;

    std::vector <std::pair<unsigned int, Texture> > getMapping() const { return _mapping; }
private:
    std::vector <std::pair<unsigned int, Texture> > _mapping;
};

