#version 330
layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vTex;

out vec2 vfTex;
uniform mat4 prmtx;

void main()
{
    vfTex = vTex;
    gl_Position = prmtx * vec4(vPosition, 0.0, 1.0);
}