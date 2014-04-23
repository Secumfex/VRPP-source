#version 330

in vec2 passUV;

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D colorMap;
uniform sampler2D specularMap;
uniform sampler2D shadowMap;

uniform mat4 uniformLightPerspective;

uniform float resX;
uniform float resY;


out vec4 fragmentColor;

void main() {
    vec4 position = texture(positionMap, passUV);
    vec4 normal = texture(normalMap, passUV);
    vec4 color = texture(colorMap, passUV);
    vec4 specularColor = texture(specularMap, passUV);
	float shininess = texture(specularMap, passUV).w;
    
    //lightPosition from camera system
    vec4 lightPos = vec4(5,2,-2,0);
    
    vec4 lightPerspective = uniformLightPerspective * position;
    
	lightPerspective = vec4(lightPerspective.xyz / lightPerspective.w, 0.0);
    lightPerspective = lightPerspective * 0.5 + 0.5;
    float lightDepth = texture(shadowMap, lightPerspective.xy).x;
    
	float visibility = 1.0;
  
 	if (lightDepth < lightPerspective.z - 0.0005) {
        visibility = 0.5;
    } else {
         visibility = 1.0;
     }
    
    //calculate lighting with given position, normal and lightposition
    vec3 nPosToLight = normalize(vec3(lightPos.xyz - position.xyz));
    
	vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
    
    vec3  reflection = normalize(reflect(-nPosToLight,normal.xyz));
    float ambient = 0.1;
    float diffuse = max(dot(normal.xyz, nPosToLight), 0) * visibility;
    float specular = pow(max(dot(reflection, -normalize(position.xyz)),0), shininess * 1000.0f);
    
    
    float resX_temp = 1.0/resX;
    float resY_temp = 1.0/resY;
    
    int strength = 5;
    
    vec4 glow = vec4(0,0,0,1);
    for(int i = -strength; i < strength; i++) {
        for(int j = -strength; j < strength; j++) {
            vec4 c = texture(colorMap, passUV + vec2(resX_temp * i, resY_temp * j));
            if(c.r + c.g + c.b > 2.0) {
                glow += c;
            }
        }
    }
    glow /= strength * strength * 4;

    fragmentColor = color * ambient + (color * diffuse  + specularColor * specular) * lightColor;
    fragmentColor += glow;
}