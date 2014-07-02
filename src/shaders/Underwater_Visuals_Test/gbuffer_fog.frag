#version 330 

in vec2 passUV;

uniform float uniformFogBegin;
uniform float uniformFogEnd;
uniform vec3 uniformFogColor;

out vec4 fragmentColor;

uniform sampler2D positionMap;	// GBuffer position map

void main() { 
	float distanceToCam = abs( texture( positionMap, passUV ).z );
	
// TODO this blows
//	if (distanceToCam == 0)
//	{
//		distanceToCam = uniformFogEnd;
//	}
	
	float fogIntensity = max( 0, min( ( distanceToCam - uniformFogBegin ) / ( uniformFogEnd - uniformFogBegin ) , 1.0 ) );
	
	fragmentColor = vec4( uniformFogColor, fogIntensity);
}