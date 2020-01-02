#pragma once

#include <vector>
#include <utility>

#include "Utilities.h"
#include "Texture.h"


class Textures {
public:
    Textures(std::vector <std::pair<unsigned int, Texture> > &mapping);
    Textures(std::vector <Texture> &textures);
    ~Textures();

    void bind() const;
    void unbind() const;

    std::vector <std::pair<unsigned int, Texture> > getMapping() const { return _mapping; }
private:
    std::vector <std::pair<unsigned int, Texture> > _mapping;
};

