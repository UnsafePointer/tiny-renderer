#pragma once
#include "Structures.hpp"

struct Texel {
    Point position;
public:
    Texel(GLfloat x, GLfloat y);
    ~Texel();
};
