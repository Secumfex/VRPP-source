#version 330 

uniform sampler2D uniformParticleTexture;

// uniform float uniformParticleDistanceMax;

in vec2 passUVCoords;
in float passDistance;
in vec3 passWorldPosition;

uniform sampler2D uniformDepthMap;
uniform float uniformWidth;
uniform float uniformHeight;

out vec4 fragmentColor;

void main() {
	if( passWorldPosition.y > 10.0 )
	{
		discard;
	}

	vec2 depthCoord = gl_FragCoord.xy;
	depthCoord.x *= uniformWidth;
	depthCoord.y *= uniformHeight;
	
	if (gl_FragDepth > texture2D(uniformDepthMap, depthCoord).x)
	{
		discard;
	}

	fragmentColor  = texture2D(uniformParticleTexture, passUVCoords);
	float distance = - passDistance;
	float maxDistance = 3.0;

	float alpha =  1.0 - pow( max ( min( (distance / maxDistance), 1.0 ), 0.0 ), 5);
    fragmentColor.w  = max( fragmentColor.w * alpha, 0.0 );
}