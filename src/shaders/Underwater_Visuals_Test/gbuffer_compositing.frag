#version 330

in vec2 passUV;

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D colorMap;

uniform mat4 uniformView;

out vec4 fragmentColor;

void main() {
    vec4 position = texture(positionMap, passUV);
    vec4 normal = texture(normalMap, passUV);
    vec4 color = texture(colorMap, passUV);
    
    //lightPosition from camera system
   // vec4 lightPos = uniformView * vec4(5,2,-2,1);
     
    // sun light direction
    vec4 lightDir = uniformView * vec4(1,1,0,0);  
        
    //calculate lighting with given position, normal and lightposition
    //vec3 nPosToLight = normalize(vec3(lightPos.xyz - position.xyz));
	
	vec3 nPosToLight = normalize(vec3( lightDir.xyz ) );
	
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec3  reflection = normalize(reflect(-nPosToLight,normal.xyz));
    float ambient = 0.2;
    float diffuse = max(dot(normal.xyz, nPosToLight), 0);
  
    fragmentColor = color * ambient + (color * diffuse );
}