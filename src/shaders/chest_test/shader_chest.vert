#version 330 core

layout(location = 0) in vec4 positionAttribute;
layout(location = 1) in vec2 uvCoordAttribute;
layout(location = 2) in vec4 normalAttribute;
layout(location = 3) in vec4 tangentAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;

out vec3 passNormal;
//out vec3 vVaryingLightDir;
out vec4 passPosition;
out vec2 passUVCoord;

out vec3 passTangent;



void main(){

vec3 vLightPosition = vec3(50,2,-2);

    // Get surface normal in eye coordinates and pass them through to the fragment shader
    passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute); 
    
    // Get vertex position in eye coordinates
    passPosition = uniformView * uniformModel * positionAttribute;
    vec3 vPosition3 = passPosition.xyz / passPosition.w;
    
    // Get vector to light source
   // vVaryingLightDir = normalize(vLightPosition - vPosition3);
    passUVCoord = uvCoordAttribute;
    
    
    gl_Position =  uniformPerspective * uniformView * uniformModel * positionAttribute;
    
    
    passTangent = vec3(transpose(inverse(uniformView * uniformModel)) * tangentAttribute);
}