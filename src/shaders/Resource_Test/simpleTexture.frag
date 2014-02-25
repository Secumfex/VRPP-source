#version 330

in vec2 passUV;

uniform sampler2D diffuseTexture;

out vec4 fragmentColor;

void main() {
    fragmentColor = texture(diffuseTexture, passUV);
}