#version 330

in vec2 passUV;

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D colorMap;
uniform sampler2D materialMap;

uniform float resX;
uniform float resY;

out vec4 fragmentColor;

void main() {
    vec4 position = texture(positionMap, passUV);
    vec4 normal = texture(normalMap, passUV);
    vec4 color = texture(colorMap, passUV);
	float shininess = texture(materialMap, passUV).x;

    //lightPosition from camera system
    vec4 lightPos = vec4(5,2,-2,1);
    
    //calculate lighting with given position, normal and lightposition
    vec3 nPosToLight = normalize(vec3(lightPos.xyz - position.xyz));


    vec3  reflection = normalize(reflect(-nPosToLight,normal.xyz));
    float ambient = 0.1;
    float diffuse = max(dot(normal.xyz, nPosToLight), 0);
    float specular = pow(max(dot(reflection, -normalize(position.xyz)),0), shininess);

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

    fragmentColor = color * ambient + color * diffuse + vec4(1,1,1,1) * specular;
    fragmentColor += glow;
}