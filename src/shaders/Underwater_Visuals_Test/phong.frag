#version 330 

in vec3 passNormal;
in vec3 passPosition;
in vec3 passLightPosition;
in vec3 passLightDirection;
in vec2 passUVCoords;

out vec4 fragmentColor;

uniform sampler2D diffuseTexture;
uniform vec3 emissiveColor;

void main() { 
    //compute the light vector as the normalized vector between 
    //the vertex position and the light position:
    vec3 lightVector = normalize(-passLightDirection);
//    float distance = dot((passLightPosition - passPosition),(passLightPosition - passPosition));
    float distance = 10.0;

    //compute the eye vector as the normalized negative vertex 
    //position in camera coordinates:
    vec3 eye = normalize(-passPosition);
    
    //compute the normalized reflection vector using 
    //GLSL's built-in reflect() function:
    vec3 reflection = normalize(reflect(-lightVector, passNormal));

    float diffuse = (max(dot(passNormal, lightVector), 0) / distance) *15.0;
    float specular = (pow(max(dot(reflection, eye), 0), 15) / distance) *10.0;
    float ambient = 0.2;

    vec3 diffuse_color = texture(diffuseTexture, passUVCoords).xyz;
    
    fragmentColor = vec4(
        diffuse  * diffuse_color + 
        specular * vec3(1, 1, 1) + 
        ambient  * diffuse_color 
        + emissiveColor 
        ,1);
}