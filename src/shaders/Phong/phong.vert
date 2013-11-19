#version 330

layout (location = 0) in vec4 positionAttribute;
layout (location = 1) in vec4 normalAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformProjection;
uniform mat4 uniformInverse;

//uniform vec4 lightPosition;

out vec3 passLightPosition;
out vec3 passPosition;
out vec3 passNormal;

void main() {
    //hardcoded light position
    vec4 lightPosition = vec4(0, 1, 1, 1);
    passLightPosition = uniformView *  lightPosition; 

    gl_Position = uniformProjection * uniformView * uniformModel * positionAttribute;

    //transform the position correctly into view space
    //and pass it to the fragment shader
    passPosition = (uniformView * uniformModel *positionAttribute).xyz;

    //transform the normal correctly into view space 
    //and pass it to the fragment shader
    passNormal = (uniformInverse * normalAttribute).xyz;
}