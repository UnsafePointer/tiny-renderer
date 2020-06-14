#pragma once
#include "Structures.hpp"

struct Pixel {
    Point screenPosition;
    Point framebufferPosition;
public:
    Pixel(Point screenPosition, Point framebufferPosition);
    ~Pixel();
};
