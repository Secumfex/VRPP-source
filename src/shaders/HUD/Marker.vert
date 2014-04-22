#version 330

layout (location = 0) in vec4 positionAttribute;

uniform vec3 uniformModelPosition;

uniform float uniformDepth;

out vec2 passUVCoords;

void main() {

	float temp = uniformDepth / 10.0;

	gl_Position = vec4( positionAttribute.x + uniformModelPosition.x, positionAttribute.y + uniformModelPosition.y +temp , 0.0, 1.0);															
   
	passUVCoords = vec2( positionAttribute.x + 0.5, positionAttribute.y + 0.5);

}