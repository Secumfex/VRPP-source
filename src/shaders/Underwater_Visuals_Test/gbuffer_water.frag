#version 330 

in vec3 passNormal;
in vec3 passPosition;
in vec3 passLightPosition;
in vec2 passUVCoords;
in vec4 passReflectionPosition;

layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;

uniform sampler2D uniformReflectionMap;
uniform sampler2D uniformRefractionMap;
uniform sampler2D uniformDepthMap;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

uniform float resX;
uniform float resY;

uniform float uniformTime;

uniform mat4 uniformInverse;

void main() { 
	positionOutput = vec4( passPosition, 1.0 );

	
	vec2 depthCoord = gl_FragCoord.xy;
	
	depthCoord.x *= 1.0 / resX;
	depthCoord.y *= 1.0 / resY;  
	
	if (gl_FragCoord.z > texture2D(uniformDepthMap, depthCoord).x)
	{
		discard;
	}
	
    float distance 		= dot( ( passLightPosition - passPosition ), ( passLightPosition - passPosition ) );
    float frag_distance = dot( passPosition , passPosition );
    float diff_strength = 1.0;

	float tile_factor 	= 0.125;
	float noise_factor 	= 0.03;
    
    vec2 texCoordNormal0 = ( passUVCoords * tile_factor );
    vec2 texCoordNormal1 = ( passUVCoords * tile_factor );
    texCoordNormal0     += sin( uniformTime / 20.0 ) * 0.3;
    texCoordNormal1.s 	-= cos( uniformTime / 20.0 ) * 0.3;
    texCoordNormal1.t 	+= cos( uniformTime / 20.0 ) * 0.3;
    
    vec3 normal0 	= texture2D( normalTexture, texCoordNormal0 ).rgb * 2.0 - 1.0;
    vec3 normal1 	= texture2D( normalTexture, texCoordNormal1 ).rgb * 2.0 - 1.0;
    vec3 normal_raw	= normalize( normal0 + normal1 );	// r == x-axis, g == z-axis, b == y-axis 
    vec3 normal 	= ( uniformInverse * vec4 ( normalize( vec3 ( normal_raw.x, normal_raw.y, normal_raw.z) ), 1.0 ) ).xyz;
    
	normalOutput = vec4( normal, 0 );
    
    vec2 texCoordReflection;
    vec2 texCoordRefraction;
    texCoordReflection.s = ( ( ( passReflectionPosition.x / passReflectionPosition.w ) / 2.0f ) + 0.5f ) + noise_factor * normal.x;
    texCoordReflection.t = ( ( ( passReflectionPosition.y / passReflectionPosition.w ) / 2.0f ) + 0.5f ) + noise_factor * normal.z;
    texCoordRefraction.s = ( gl_FragCoord.x / 800.0 )   + noise_factor * normal.x;
    texCoordRefraction.t = ( gl_FragCoord.y / 600.0 )   + noise_factor * normal.z;
    
    vec3 lightVector 		= normalize( passLightPosition - passPosition );
    vec3 reflectionVector 	= normalize( reflect( -lightVector, normal ) );
    
    vec3 eyeVector = normalize(-passPosition);
    float viewAngle = abs ( dot ( eyeVector, normal ) ); // 0 --> close to parallel , 1 --> close to orthogonal
    float reflection = 1.0 - viewAngle;
    float refraction = viewAngle;

    float diffuse 	= ( max( dot( normal, lightVector ), 0 ) );
    float specular 	= ( pow( max( dot( reflectionVector , eyeVector ), 0), 25) );
    float ambient 	= 0.2;

    vec3 diffuse_color_texture 		= texture( diffuseTexture, texCoordNormal0 ).xyz;
    vec3 diffuse_color_reflection 	= texture( uniformReflectionMap, texCoordReflection ).xyz;
    vec3 diffuse_color_refraction   = texture( uniformRefractionMap, texCoordRefraction ).xyz;
    vec3 diffuse_color 	= ( 
            diffuse_color_reflection    * reflection 
//        +   diffuse_color_texture       * 0.5
        +   diffuse_color_refraction    * refraction) 
//    / 1.5f
    ;
    
    colorOutput 	= vec4(
        ( diffuse  * diffuse_color   +
          specular * vec3( 1, 1, 1 ) + 
          ambient  * diffuse_color ) 
        * diff_strength , 1.0);
}