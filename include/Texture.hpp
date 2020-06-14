#pragma once
#include <glad/glad.h>
#include <memory>

class Texture {
public:
    GLuint object;
    GLsizei width;
    GLsizei height;

    Texture(GLsizei width, GLsizei height);
    ~Texture();

    void bind(GLenum texture);
};
