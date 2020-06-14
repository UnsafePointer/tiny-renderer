#include "Vertex.hpp"

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) {
    position = {x, y};
    color = {r, g, b};
}

Vertex::~Vertex() {

}
