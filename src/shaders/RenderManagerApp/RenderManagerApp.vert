#version 330 core

layout (location = 0) in vec3 pos; 

uniform mat4 uniformMVP; 

out vec4 Color; 

void main() 
{ 
    gl_Position = uniformMVP * vec4(pos, 1); 
    Color = vec4(clamp(pos, 0, 1), 1); 
} 