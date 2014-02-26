#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;

uniform float shininess;

uniform sampler2D diffuseTexture;

//writable textures for deferred screen space calculations

layout(location = 4) out vec4 shadowOutput;
 
void main(){  
    shadowOutput = vec4(texture(diffuseTexture, passUVCoord).rgb, passPosition.z);
}
