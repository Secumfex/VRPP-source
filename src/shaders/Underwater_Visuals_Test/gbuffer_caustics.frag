#version 330 

in vec2 passUV;

uniform mat4 uniformView;
uniform mat4 uniformProjectorViewPerspective;

uniform vec3 uniformSunDirection;

out vec4 fragmentColor;

uniform sampler2D positionMap;	// GBuffer position map
uniform sampler2D normalMap;	// GBuffer normal 	map
uniform sampler2D colorMap;		// GBuffer color 	map
uniform sampler2D uniformCausticsTexture;

uniform float uniformTime;

void main() { 
	vec4 color = texture(colorMap, passUV);
	vec4 normal = texture(normalMap, passUV);
	vec4 position = texture(positionMap, passUV);	// to be interpreted as depth information

	//	float distanceToCamera = abs ( position.z );

	// invert view matrix with camera position --> world position
	vec4 worldPos = inverse ( uniformView ) *  position;
	
	if ( worldPos.y > 10.0f )
	{
		discard;
	}
	
	vec4 projectedPos = uniformProjectorViewPerspective * worldPos;
	
	vec4 sunDirection = ( uniformView * vec4( uniformSunDirection, 0) );
	
	float lightIntensity = max( 0.0, dot ( normal.xyz, sunDirection.xyz ) * ( - 1.0 ) );
	
    // CAUSTICS AND GOD RAY TEXTURE OFFSET //////////////////
    float tile_factor   = 3.0f;
    float noise_factor  = 0.3f;

    vec2 sampling_offset0 = vec2(0.0, 0.0) + sin( uniformTime / 3.0) * noise_factor;
    vec2 sampling_offset1 = vec2(0.0, 0.0);
    sampling_offset1.s   -= cos( uniformTime / 3.0) * noise_factor;
    sampling_offset1.t   += cos( uniformTime / 3.0) * noise_factor;

    /////////////////////////////////////////////////////////
    // CAUSTICS /////////////////////////////////////////////
    vec2 projectedUVCoords0 = (projectedPos.xy) / projectedPos.w ;
    vec2 projectedUVCoords1 = projectedUVCoords0;

    projectedUVCoords0 *= tile_factor;
    projectedUVCoords1 *= tile_factor;  

    projectedUVCoords0 += sampling_offset0;
    projectedUVCoords1 += sampling_offset1;
    
    vec3 caustics0   = texture2D( uniformCausticsTexture, projectedUVCoords0 ).rgb;
    vec3 caustics1   = texture2D( uniformCausticsTexture, projectedUVCoords1 ).rgb;
    vec3 caustics    = ( caustics0 + caustics1 ) / 1.5; 

    // ////// /////////////////////////////////////////////
    
    fragmentColor = vec4( caustics * 2.0 * color.rgb * lightIntensity, 1);
}