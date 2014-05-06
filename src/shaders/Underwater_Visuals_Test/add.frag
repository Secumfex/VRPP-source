#version 330

in vec2 passUV;

uniform sampler2D uniformBaseTexture;
uniform sampler2D uniformAddTexture;

out vec4 fragmentColor;

// a shader which adds the color of one texture on top of the other, taking alpha value of add texture into account
void main() {
	vec4 base = texture( uniformBaseTexture, passUV);
	vec4 add = texture(  uniformAddTexture,  passUV);

	float add_alpha = add.w;

	vec4 color = base + add * add_alpha;

    fragmentColor = vec4( color );
}