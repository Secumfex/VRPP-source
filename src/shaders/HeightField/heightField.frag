#version 330 

in vec3 normalPass;
in vec3 positionPass;
in vec2 uvCoordPass;

uniform sampler2D uniformTexture1;
uniform sampler2D uniformTexture2;
uniform sampler2D uniformTextureMask;


void main() { 

vec4 color1 = texture2D(uniformTexture1,uvCoordPass);
vec4 color2 = texture2D(uniformTexture2,uvCoordPass);
vec4 mask = texture2D(uniformTextureMask,uvCoordPass);

gl_FragColor = mask*color1 + (1-mask)*color2;

}