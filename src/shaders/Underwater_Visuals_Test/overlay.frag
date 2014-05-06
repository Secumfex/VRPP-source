#version 330

in vec2 passUV;

uniform sampler2D uniformBaseTexture;
uniform sampler2D uniformOverlayTexture;

out vec4 fragmentColor;

// a shader which overlays a texture ontop of another, based on its alpha value
void main() {
	vec4 base    = texture( uniformBaseTexture,    passUV);
	vec4 overlay = texture( uniformOverlayTexture, passUV);

	float overlay_alpha = overlay.w;

    vec4 color  = mix( base, overlay, overlay_alpha );

    fragmentColor = color;
}