#version 330 

uniform sampler2D uniformAirTexture;

in vec2 passUVCoords;

out vec4 fragmentColor;

void main() {
		fragmentColor  = texture2D(uniformAirTexture, passUVCoords);
}