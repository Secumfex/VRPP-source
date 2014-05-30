#version 330 

in vec2 passUVs;

in vec4 passProjectedPos;
in vec3 passWorldPos;

uniform vec3 uniformCameraWorldPos;
uniform mat4 uniformProjectorViewPerspective;

out vec4 fragmentColor;

uniform sampler2D uniformDepthMap;
uniform sampler2D uniformCausticsTexture;

uniform float uniformTime;

void main() { 

    // CAUSTICS AND GOD RAY TEXTURE OFFSET //////////////////
    float tile_factor   = 3.0f;
    float noise_factor  = 0.3f;

    vec2 sampling_offset0 = vec2(0.0, 0.0) + sin( uniformTime / 3.0) * noise_factor;
    vec2 sampling_offset1 = vec2(0.0, 0.0);
    sampling_offset1.s   -= cos( uniformTime / 3.0) * noise_factor;
    sampling_offset1.t   += cos( uniformTime / 3.0) * noise_factor;

    /////////////////////////////////////////////////////////
    // CAUSTICS /////////////////////////////////////////////
    vec2 projectedUVCoords0 = (passProjectedPos.xy) / passProjectedPos.w ;
    vec2 projectedUVCoords1 = projectedUVCoords0;

    projectedUVCoords0 *= tile_factor;
    projectedUVCoords1 *= tile_factor;  

    projectedUVCoords0 += sampling_offset0;
    projectedUVCoords1 += sampling_offset1;
    
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