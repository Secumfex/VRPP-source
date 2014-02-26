#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;

uniform float shininess;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform mat4 uniformLightProjection;

//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
layout(location = 3) out vec4 materialOutput;
 
void main(){  

	vec4 lightProjection = uniformLightProjection * passPosition;

	vec3 lightProjection = lightProjection.xyz / lightProjection.w;
    lightProjection = lightProjection * 0.5 + 0.5;

	float visibility = 1.0;

    positionOutput = passPosition;
    normalOutput = vec4(normalize(passNormal), 0);
    colorOutput = vec4(texture(diffuseTexture, passUVCoord).rgb, visibility);
    materialOutput = vec4(shininess, 0.0, 0.0, 0.0);
}
