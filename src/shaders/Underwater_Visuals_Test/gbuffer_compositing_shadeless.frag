#version 330

in vec2 passUV;

uniform sampler2D colorMap;

out vec4 fragmentColor;

void main() {

    vec4 color = texture(colorMap, passUV);
    fragmentColor = color;

}