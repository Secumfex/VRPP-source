#version 330

in vec2 vfTex;

uniform sampler2D fboTex;

void main()
{
    gl_FragColor = texture2D(fboTex, vfTex);
}