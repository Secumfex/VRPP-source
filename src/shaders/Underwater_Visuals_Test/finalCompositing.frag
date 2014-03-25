#version 330

in vec2 passUV;

uniform sampler2D uniformPreCompositionMap;
uniform sampler2D uniformGodRayMap;

out vec4 fragmentColor;

void main() {
    fragmentColor = texture( uniformPreCompositionMap, passUV) + texture( uniformGodRayMap, passUV);
}