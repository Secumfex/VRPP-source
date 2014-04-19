#version 330

in vec3 lightPosition;

//layout(location = 0) in vec4 positionIn;
//layout(location = 1) in vec4 colorIn;
//layout(location = 2) in vec4 normalIn;
//layout(location = 3) in vec4 specularIn;

uniform sampler2D positionOut;
uniform sampler2D colorOut;
uniform sampler2D normalOut;
uniform sampler2D specularOut;

//phong mit allen maps

out vec4 fragmentColor = ;


void main{

	
	//daten aus maps
	float diffuse = ;
	float specular = ;
	float ambient = ;

	fragmentColor = vec4(diffuse*vec3(1,0,0)+specular*vec3(1,1,1)+ambient*vec3(1,0.5,0.5),1);
}