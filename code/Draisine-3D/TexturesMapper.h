#pragma once

#include <vector>
#include <utility>

#include "Utilities.h"
#include "Texture.h"
#include "Shader.h"


class TexturesMapper {
public:
    TexturesMapper(std::vector <std::pair<std::string, Texture&> > &mapping, Shader &shader);
    ~TexturesMapper();

    void bind() const;
    void unbind() const;

    std::vector <std::pair<std::string, Texture&> > getMapping() const { return _mapping; }
private:
    std::vector <std::pair<std::string, Texture&> > &_mapping;
    Shader &_shader;
};

