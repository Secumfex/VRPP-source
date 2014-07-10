#version 330

in vec2 passUV;

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D colorMap;
uniform sampler2D uniformDepthMap;

uniform mat4 uniformView;
uniform mat4 uniformProjectorViewPerspective;

uniform vec3 uniformSunDirection;
uniform vec3 uniformCameraWorldPos;

out vec4 fragmentColor;

void main() {
    vec4 position = texture(positionMap, passUV);			// position in camera coordinates
    vec4 normal = texture(normalMap, passUV);
    vec4 color = texture(colorMap, passUV);
    
  //try
      vec4 fragPosition = inverse(uniformView) * position; 	// world position of fragment

      vec4 shadowCoord = uniformProjectorViewPerspective * ( fragPosition - vec4( uniformCameraWorldPos, 0) );	// position of fragment in sun perspective

      shadowCoord /= shadowCoord.w;	// position in kanonisches volumen
      shadowCoord.xyz = ( shadowCoord.xyz * 0.5 ) + 0.5;	// position between [0,1]
      
      float visibility = 0.1;
      if ( shadowCoord.x >= 1.0 || shadowCoord.x <= 0.0 || shadowCoord.y <= 0.0 || shadowCoord.y >= 1.0 )
      {
    	  visibility = 1.0;
      }
      else
      {
    	  if ( texture ( uniformDepthMap, shadowCoord.xy ).z > shadowCoord.z - 0.01 )
    	  {
    	     visibility = 1.0;
    	  }	  
      }
     
  //\try
    
    vec3 lightDir = normalize ( (transpose(inverse(uniformView)) * vec4 (uniformSunDirection, 0 ) ).xyz );
    

	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec3  reflection = normalize(reflect( lightDir, normal.xyz));
    float ambient = 0.2;
    float diffuse = max(dot(normal.xyz, -lightDir ), 0);
  	
  	vec4 finalColor = vec4( 0,0,0,0);
    finalColor.rgb = ambient * color.rgb;
  	finalColor.rgb +=  color.rgb * ( max( diffuse * visibility - ambient, 0 ) );
  	finalColor.a = color.a;
  	
  //	finalColor = vec4 ( shadowCoord.xyz, 1.0);
  	
    fragmentColor = finalColor;
}