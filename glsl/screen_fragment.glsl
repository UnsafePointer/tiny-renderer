#version 330 core
out vec4 FragColor;

in vec2 fragmentTexturePosition;

uniform sampler2D screenTexture;

void main() {
    FragColor = texture(screenTexture, fragmentTexturePosition);
}
