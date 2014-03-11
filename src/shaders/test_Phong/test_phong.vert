#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;

out vec3 position;
out vec3 normal;


uniform mat4 modelviewMatrix;
uniform mat4 projectionMatrix;

void main() {
	mat3 normalMatrix = mat3( transpose( inverse( modelviewMatrix )));
	normal = normalize(normalMatrix * vertexNormal); // normal in viewspace
	position = vec3(modelviewMatrix * vec4(vertexPosition, 1.0)); // position in viewspace
	gl_Position = projectionMatrix * modelviewMatrix * vec4(vertexPosition, 1.0); // position in clip-coordinates
	}