#version 330

in vec2 passUV;
in vec4 vertPos;

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D colorMap;
uniform sampler2D uniformDepthMap;

uniform mat4 uniformView;
uniform mat4 uniformProjectorViewPerspective;
uniform mat4 uniformDepthBiasMVP;

uniform vec3 uniformSunDirection;

out vec4 fragmentColor;

void main() {

  //try
      vec4 shadowCoord = uniformDepthBiasMVP * vertPos;
      float visibility = 0.001;
      if ( texture ( uniformDepthMap, shadowCoord.xy ).z < shadowCoord.z){
          visibility = 1.0;
      }
  //\try

    vec4 position = texture(positionMap, passUV);
    vec4 normal = texture(normalMap, passUV);
    vec4 color = texture(colorMap, passUV);
    
    //lightPosition from camera system
   // vec4 lightPos = uniformView * vec4(5,2,-2,1);
     
    // sun light direction
 //   vec4 lightDir = uniformView * vec4(1,1,0,0);  
    
    vec3 lightDir = normalize ( (transpose(inverse(uniformView)) * vec4 (uniformSunDirection, 0 ) ).xyz );
    
    //calculate lighting with given position, normal and lightposition
    //vec3 nPosToLight = normalize(vec3(lightPos.xyz - position.xyz));
	
//	vec3 nPosToLight = - normalize(vec3( lightDir.xyz ) );
	
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec3  reflection = normalize(reflect( lightDir, normal.xyz));
    float ambient = 0.2;
    float diffuse = max(dot(normal.xyz, -lightDir ), 0);
  	
  	vec4 finalColor = vec4( 0,0,0,0);
    finalColor.rgb = ambient * color.rgb;
  	finalColor.rgb +=  color.rgb * ( max(diffuse - ambient, 0 ) );
    finalColor.rgb = visibility * finalColor.rgb;
  	finalColor.a = color.a;
    fragmentColor = finalColor;
}