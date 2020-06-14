#include "Framebuffer.hpp"
#include "Texture.hpp"

using namespace std;

Framebuffer::Framebuffer(unique_ptr<Texture> &texture) {
    glGenFramebuffers(1, &object);
    glBindFramebuffer(GL_FRAMEBUFFER, object);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->object, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glViewport(0, 0, texture->width, texture->height);
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &object);
}
