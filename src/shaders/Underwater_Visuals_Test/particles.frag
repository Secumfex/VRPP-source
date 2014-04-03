#version 330 

uniform sampler2D uniformParticleTexture;

in vec2 passUVCoords;

out vec4 fragmentColor;

void main() {
	fragmentColor  = texture2D(uniformParticleTexture, passUVCoords);
	float distance = gl_FragCoord.z / gl_FragCoord.w;

    fragmentColor.w *= ( 1.0 - ( distance / 2.0 ) );
    fragmentColor.w  = max( fragmentColor.w, 0.0 );
}