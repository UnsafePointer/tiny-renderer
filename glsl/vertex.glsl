#version 330 core
in vec2 position;
in vec3 color;

uniform vec2 offset;

out vec3 fragmentColor;

void main() {
    vec2 position = position + offset;

    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    fragmentColor = color;
}
