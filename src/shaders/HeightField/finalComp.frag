#version 330

in vec3 lightPosition;
in vec2 uvCoods;

uniform sampler2D positionOut;
uniform sampler2D colorOut;
uniform sampler2D normalOut;
uniform sampler2D specularOut;


out vec4 fragmentColor;


void main{

	
	
	//daten aus maps
	float diffuse = texture2D(colorOut,uvCoords);
	float normals = texture2D(normalOut,uvCoods);
	float specular = texture2D(specular,uvCoords);
	float ambient = 0.3;

	fragmentColor = vec4(diffuse*vec3(1,0,0)+specular*vec3(1,1,1)+ambient*vec3(1,0.5,0.5),1);
}