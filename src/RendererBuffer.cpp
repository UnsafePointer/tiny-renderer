#include "RendererBuffer.hpp"
#include <stddef.h>
#include <iostream>
#include "Vertex.hpp"

using namespace std;

template <class T>
RendererBuffer<T>::RendererBuffer(unique_ptr<RendererProgram> &program, uint capacity) : vao(make_unique<VertexArrayObject>()), program(program), capacity(capacity), size(0) {
    glGenBuffers(1, &vbo);

    vao->bind();
    bind();

    GLsizeiptr bufferSize = sizeof(T) * capacity;
    glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
    enableAttributes();
}

template <class T>
RendererBuffer<T>::~RendererBuffer() {
    glDeleteBuffers(1, &vbo);
}

template <class T>
void RendererBuffer<T>::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

template <class T>
void RendererBuffer<T>::clean() {
    bind();
    GLsizeiptr bufferSize = sizeof(T) * capacity;
    glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
    size = 0;
}

template <class T>
void RendererBuffer<T>::addData(vector<T> data) {
    uint remainingCapacity = capacity - size;
    if (data.size() > remainingCapacity) {
        cout << "Renderer buffer out of memory." << endl;
        exit(1);
    }
    bind();

    uint offset = size * sizeof(T);
    uint dataSize = data.size() * sizeof(T);
    glBufferSubData(GL_ARRAY_BUFFER, offset, dataSize, data.data());

    size += data.size();
}

template <class T>
void RendererBuffer<T>::draw() {
    vao->bind();
    program->useProgram();
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)size);
    clean();
}

template <>
void RendererBuffer<Vertex>::enableAttributes() const {
    GLuint positionIdx = program->findProgramAttribute("position");
    glVertexAttribPointer(positionIdx, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, position));
    glEnableVertexAttribArray(positionIdx);

    GLuint colorIdx = program->findProgramAttribute("color");
    glVertexAttribPointer(colorIdx, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, color));
    glEnableVertexAttribArray(colorIdx);
}

template class RendererBuffer<Vertex>;
