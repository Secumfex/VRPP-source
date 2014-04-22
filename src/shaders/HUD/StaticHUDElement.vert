#version 330

layout (location = 0) in vec4 positionAttribute;

uniform vec3 uniformModelPosition;

out vec2 passUVCoords;

void main() {

	gl_Position = vec4( positionAttribute.x + uniformModelPosition.x, positionAttribute.y + uniformModelPosition.y, 0.0, 1.0);															
   
	passUVCoords = vec2( positionAttribute.x + 0.5, positionAttribute.y + 0.5);

}