#include "Texture.hpp"

using namespace std;

Texture::Texture(GLsizei width, GLsizei height) : width(width), height(height) {
    glGenTextures(1, &object);
    glBindTexture(GL_TEXTURE_2D, object);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB5_A1, width, height);
}

Texture::~Texture() {
    glDeleteTextures(1, &object);
}

void Texture::bind(GLenum texture) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, object);
}
