#version 330 core

layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;

uniform vec4 uniformClearPosition;
uniform vec4 uniformClearNormal;
uniform vec4 uniformClearColor;
 
void main(){  
    positionOutput = uniformClearPosition;
    normalOutput = uniformClearNormal;
    colorOutput = uniformClearColor;    
}