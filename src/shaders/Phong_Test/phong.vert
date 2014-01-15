#version 330

layout (location = 0) in vec4 positionAttribute;
layout (location = 2) in vec4 normalAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformInverse;
uniform mat4 uniformProjection;

out vec3 passNormal;
out vec3 passLightPosition;
out vec3 passPosition;

void main() {
    passLightPosition = (uniformView * vec4(-3,3,2,1)).xyz;

    gl_Position = uniformProjection * uniformView * uniformModel * positionAttribute;

    //transform the position correctly into view space
    //and pass it to the fragment shader
    passPosition = (uniformView * uniformModel * positionAttribute).xyz;

    //transform the normal correctly into view space 
    //and pass it to the fragment shader
    passNormal = normalize((uniformInverse * normalAttribute).xyz);
}