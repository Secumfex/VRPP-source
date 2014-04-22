
in vec2 passUV;

uniform sampler2D uniformPreCompositionMap;
uniform sampler2D uniformGodRayMap;
uniform sampler2D uniformParticlesMap;

out vec4 fragmentColor;

void main() {
	vec4 preComposition = texture( uniformPreCompositionMap, passUV);
	vec4 particles = texture( uniformParticlesMap, passUV);
	vec4 godRay =  texture( uniformGodRayMap, passUV);
	
	float part_alpha = particles.w;

	vec3 color 	= preComposition.rgb * (1.0 - part_alpha) + particles.rgb * (part_alpha);
	godRay 		*= 1.0;
	color 		+= godRay.rgb;
    fragmentColor = vec4( color, 1.0);
}