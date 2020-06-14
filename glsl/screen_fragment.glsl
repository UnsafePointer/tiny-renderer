#version 330 core
in vec2 fragmentTexturePosition;

uniform sampler2D framebufferTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(framebufferTexture, fragmentTexturePosition);
}
