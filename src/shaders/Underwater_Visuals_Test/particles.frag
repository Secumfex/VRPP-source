#version 330 

in vec2 passUVCoords;

out vec4 fragmentColor;

uniform sampler2D uniformParticleTexture;

void main() {
    fragmentColor = texture(uniformParticleTexture, passUVCoords);
}