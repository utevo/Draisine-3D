#pragma once

#include <vector>

#include "Utilities.h"


struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() :
        _pointerToNextElement(0) { }

    void addFloat(unsigned int count) { _push(GL_FLOAT, count, GL_FALSE); }
    void addUnsignedInt(unsigned int count) { _push(GL_UNSIGNED_INT, count, GL_FALSE); }
    void addUnsignedByte(unsigned int count) { _push(GL_UNSIGNED_BYTE, count, GL_TRUE); }

    const std::vector<VertexBufferElement> getElements() const { return _elements; };
    unsigned int getPointerToNextElement() const { return _pointerToNextElement; };

private:
    unsigned int _pointerToNextElement;
    std::vector<VertexBufferElement> _elements;

    void _push(unsigned int type, unsigned int count, unsigned char normalized) {
        _elements.push_back({ type, count, normalized });
        _pointerToNextElement += count * GLGetSizeOfType(type);
    };


};