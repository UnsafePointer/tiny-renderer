#pragma once
#include <glad/glad.h>
#include "Structures.hpp"

struct Vertex {
    Point position;
    Color color;
public:
    Vertex(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b);
    Vertex(Point position, Color color);
    ~Vertex();
};
