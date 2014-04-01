#version 330

in vec2 passUV;

uniform sampler2D uniformPreCompositionMap;
uniform sampler2D uniformGodRayMap;
uniform sampler2D uniformParticlesMap;

out vec4 fragmentColor;

void main() {
	vec3 preComposition = texture( uniformPreCompositionMap, passUV).xyz;
	vec3 particles = texture( uniformParticlesMap, passUV).xyz;
	vec3 godRay =  texture( uniformGodRayMap, passUV).xyz;
	godRay *= 1.0;
    fragmentColor = vec4( preComposition + godRay + particles, 1.0);
}