#version 330 

layout(location = 0) out float fragmentdepth;

uniform sampler2D uniformDepthMap;

void main() { 

	fragmentdepth = gl_FragCoord.z;
	
}