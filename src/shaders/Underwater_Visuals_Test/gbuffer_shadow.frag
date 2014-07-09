#version 330 

layout(location = 0) out vec4 positionOutput;

uniform sampler2D uniformDepthMap;

void main() { 

	fragmentdepth = gl_FragCoord.z;
}