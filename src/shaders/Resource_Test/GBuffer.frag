#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;

uniform float shininess;
uniform vec3 specularColor;

uniform vec3 diffuseColor;

uniform sampler2D diffuseTexture;


//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
layout(location = 3) out vec4 materialOutput;
 
void main(){  

    positionOutput = vec4(vec3(passPosition.xyz),diffuseColor.r);
    normalOutput = vec4(normalize(passNormal), diffuseColor.g);
    colorOutput=texture(diffuseTexture, passUVCoord);
    materialOutput = vec4(specularColor, diffuseColor.b);

}