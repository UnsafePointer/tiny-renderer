#version 330 core
in vec2 position;
in vec2 texturePosition;

out vec2 fragmentTexturePosition;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    fragmentTexturePosition = texturePosition;
}
