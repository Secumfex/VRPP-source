#version 330 

in vec3 passNormal;
in vec3 passPosition;
in vec3 passLightPosition;
in vec2 passUVCoords;
in vec4 passProjectedPos;

out vec4 fragmentColor;

uniform sampler2D diffuseTexture;
uniform sampler2D uniformCausticsTexture;
uniform vec3  emissiveColor;

uniform float uniformFogBegin;
uniform float uniformFogEnd;
uniform vec3  uniformFogColor;

uniform float uniformTime;

void main() { 
    //compute the light vector as the normalized vector between 
    //the vertex position and the light position:
    vec3 lightVector = normalize(passLightPosition - passPosition);
    float distance = dot((passLightPosition - passPosition),(passLightPosition - passPosition));

    float frag_distance = dot(passPosition,passPosition);

    float fog_strength = min(max((frag_distance - uniformFogBegin) / (uniformFogEnd - uniformFogBegin),0.0),1.0);
    float diff_strength = 1.0 - fog_strength;
    //compute the eye vector as the normalized negative vertex 
    //position in camera coordinates:
    vec3 eye = normalize(-passPosition);
    
    //compute the normalized reflection vector using 
    //GLSL's built-in reflect() function:
    vec3 reflection = normalize(reflect(-lightVector, passNormal));

    float diffuse = (max(dot(passNormal, lightVector), 0) );
    float specular = (pow(max(dot(reflection, eye), 0), 15) ) *1.0;
    float ambient = 0.2;

    vec3 diffuse_color = texture(diffuseTexture, passUVCoords).xyz;

    // CAUSTICS /////////////////////////////////////////////
    vec2 projectedUVCoords0 = (passProjectedPos.xy) / passProjectedPos.w ;
    vec2 projectedUVCoords1 = projectedUVCoords0;

    float tile_factor   = 4.0f;
    float noise_factor  = 0.03f;
    
    projectedUVCoords0 *= tile_factor;
    projectedUVCoords1 *= tile_factor;  

    projectedUVCoords0     += sin( uniformTime / 3.0) * 0.3;
    projectedUVCoords1.s   -= cos( uniformTime / 3.0) * 0.3;
    projectedUVCoords1.t   += cos( uniformTime / 3.0) * 0.3;
    
    vec3 caustics0   = texture2D( uniformCausticsTexture, projectedUVCoords0 ).rgb;
    vec3 caustics1   = texture2D( uniformCausticsTexture, projectedUVCoords1 ).rgb;
    vec3 caustics    = ( caustics0 + caustics1 ) / 1.5; 

    diffuse_color += diffuse_color * caustics;
    // ////// /////////////////////////////////////////////


    
    fragmentColor = vec4(
        vec3(
        diffuse  * diffuse_color +
        specular * vec3(1, 1, 1) + 
        ambient  * diffuse_color 
        ) 
        * diff_strength + fog_strength *uniformFogColor
        + emissiveColor 
        ,1);
}