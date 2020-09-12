#pragma once
#include <glad/glad.h>
#include <memory>
#include <vector>
#include "VertexArrayObject.hpp"
#include "RendererProgram.hpp"

template <class T>
class RendererBuffer {
    std::unique_ptr<VertexArrayObject> vao;
    GLuint vbo;
    std::unique_ptr<RendererProgram> &program;
    unsigned int capacity;
    unsigned int size;

    void enableAttributes() const;
public:
    RendererBuffer(std::unique_ptr<RendererProgram> &program, unsigned int capacity);
    ~RendererBuffer();

    void bind() const;
    void clean();
    void addData(std::vector<T> data);
    void draw(GLenum mode);
};
