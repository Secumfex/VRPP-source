#version 330 

in vec3 normalPass
in vec3 positionPass
in vec2 uvCoordPass

uniform sampler2D texture1
uniform sampler2D texture2
uniform sampler2D textureMask


void main() { 

vec4 color1 = texture2D(texture1,uvCoordPass);
vec4 color2 = texture2D(texture2,uvCoordPass);
vec4 mask = texture2D(textureMask,uvCoordPass);

gl_FragColor = mask*color1 + (1-mask)*color2;

}