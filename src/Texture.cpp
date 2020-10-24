#include "Texture.hpp"

using namespace std;

Texture::Texture(GLsizei width, GLsizei height) : width(width), height(height) {
    glGenTextures(1, &object);
    glBindTexture(GL_TEXTURE_2D, object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width, height);
}

Texture::~Texture() {
    glDeleteTextures(1, &object);
}

void Texture::bind(GLenum texture) {
    (void)texture;
    // glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, object);
}
