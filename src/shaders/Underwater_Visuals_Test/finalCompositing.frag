#version 330

in vec2 passUV;

uniform sampler2D uniformPreCompositionMap;
uniform sampler2D uniformGodRayMap;

out vec4 fragmentColor;

void main() {
	vec4 preComposition = texture( uniformPreCompositionMap, passUV);
	vec4 godRay =  texture( uniformGodRayMap, passUV);
	godRay *= 1.0;
    fragmentColor = preComposition + godRay;
}