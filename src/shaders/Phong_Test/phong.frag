#version 330 

in vec3 passNormal;
in vec3 passPosition;
in vec3 passLightPosition;

out vec4 fragmentColor;

void main() { 
    //compute the light vector as the normalized vector between 
    //the vertex position and the light position:
    vec3 lightVector = normalize(passLightPosition - passPosition);
    float distance = dot((passLightPosition - passPosition),(passLightPosition - passPosition));

    //compute the eye vector as the normalized negative vertex 
    //position in camera coordinates:
    vec3 eye = normalize(-passPosition);
    
    //compute the normalized reflection vector using 
    //GLSL's built-in reflect() function:
    vec3 reflection = normalize(reflect(-lightVector, passNormal));

    //comment in to use the phong lighting model:
    float diffuse = (max(dot(passNormal, lightVector), 0) / distance) *15.0;
    float specular = (pow(max(dot(reflection, eye), 0), 15) / distance) *10.0;
    float ambient = 0.3;

    fragmentColor = vec4(
    //comment in to use the phong lighting model:
        diffuse  * vec3(1, 0, 0) + 
        specular * vec3(1, 1, 1) + 
        ambient  * vec3(1, 0.5, 0.5), 
        1);
       //fragmentColor = vec4(1,0,0,1);
}