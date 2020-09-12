#include "Vertex.hpp"

Vertex::Vertex(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b) {
    position = {x, y};
    color = {r, g, b};
}

Vertex::Vertex(Point position, Color color) : position(position), color(color) {

}

Vertex::~Vertex() {

}

Pixel::Pixel(Point position, Point texturePosition) : position(position), texturePosition(texturePosition) {}

Pixel::~Pixel() {}
