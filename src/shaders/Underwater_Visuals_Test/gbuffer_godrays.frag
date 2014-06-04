#version 330 

in vec2 passUV;

out vec4 fragmentColor;

uniform vec3 uniformCameraWorldPos;

uniform mat4 uniformView;
uniform mat4 uniformProjectorViewPerspective;

uniform sampler2D positionMap;
uniform sampler2D uniformCausticsTexture;
// uniform sampler2D uniformWaterObjectDepthMap;

uniform float uniformTime;

void main() { 
	vec4 position = texture(positionMap, passUV);	// to be interpreted as depth information
	float distanceToCamera = abs ( position.z );

	// invert view matrix with camera position --> world position
	vec4 worldPos = inverse ( uniformView ) *  position;
	
    // CAUSTICS AND GOD RAY TEXTURE OFFSET //////////////////
    float tile_factor   = 3.0f;
    float noise_factor  = 0.3f;

    vec2 sampling_offset0 = vec2(0.0, 0.0) + sin( uniformTime / 3.0) * noise_factor;
    vec2 sampling_offset1 = vec2(0.0, 0.0);
    sampling_offset1.s   -= cos( uniformTime / 3.0) * noise_factor;
    sampling_offset1.t   += cos( uniformTime / 3.0) * noise_factor;
    // ////// /////////////////////////////////////////////
    // GOD RAYS ///////////////////////////////////////////
    int samples = 48;
    float xz_step  = 0.015625;
    float max_depth = 10.0;
    float water_height = 10.0;
    vec3 god_ray_strength = vec3(0.0, 0.0, 0.0);
    
//    float mesh_distance_to_camera = dot ( passWorldPos - uniformCameraWorldPos, passWorldPos - uniformCameraWorldPos );
    float mesh_distance_to_camera = distanceToCamera;

    vec3 sample = uniformCameraWorldPos;
//    vec3 view_ray_direction = normalize( passWorldPos - uniformCameraWorldPos );
    vec3 view_ray_direction = normalize( worldPos.xyz - uniformCameraWorldPos );

    for ( int i = 0; i < samples; i++ )
    {
        //vec3 view_ray_xz = vec3( view_ray_direction.x, 0.0, view_ray_direction.z);
        //float ray_step = dot ( view_ray_xz, view_ray_xz ) * xz_step;
        float ray_step = xz_step;
        xz_step *= 1.1;
        sample += view_ray_direction * ray_step;

        float depth_factor = min( max ( ( 1.0 - ( ( water_height - sample.y ) / max_depth ) ), 0.0), 1.0);
        float sample_distance_to_camera = dot ( sample - uniformCameraWorldPos, sample - uniformCameraWorldPos );

        if (sample_distance_to_camera > mesh_distance_to_camera){
            break;
        }
        if (depth_factor == 0.0 || depth_factor == 1.0){
            continue;
        }

        vec4 projectedSample = uniformProjectorViewPerspective * vec4( sample.xyz, 1.0);
        projectedSample = vec4( ( projectedSample.xyz / projectedSample.w ), 1.0);
        
        vec2 projectedSampleUVCoords0 = projectedSample.xy;
        vec2 projectedSampleUVCoords1 = projectedSample.xy;

        projectedSampleUVCoords0 *= tile_factor;
        projectedSampleUVCoords1 *= tile_factor;  

        projectedSampleUVCoords0 += sampling_offset0;
        projectedSampleUVCoords1 += sampling_offset1;
        
        vec3 sample_color0   = texture2D( uniformCausticsTexture, projectedSampleUVCoords0 ).rgb;
        vec3 sample_color1   = texture2D( uniformCausticsTexture, projectedSampleUVCoords1 ).rgb;
        vec3 sample_color    = ( sample_color0 + sample_color1 ) * ( depth_factor ); 
        
        god_ray_strength += sample_color * sample_color;
    }

   god_ray_strength /= samples / 4.0;
    // ////// /////////////////////////////////////////////
    
    fragmentColor = vec4(
        god_ray_strength * vec3(1.0, 1.0, 1.0)
        ,1);
}