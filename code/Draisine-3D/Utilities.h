#pragma once

#include <assert.h>

#include "Debug.h"


#ifdef DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())
#else
#define GLCall(x) x
#endif

static unsigned int GLGetSizeOfType(unsigned int type)
{
    switch (type)
    {
    case GL_FLOAT: return sizeof(GLfloat);
    case GL_UNSIGNED_INT: return sizeof(GLuint);
    case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
    }
    ASSERT(false);
    return 0;
}