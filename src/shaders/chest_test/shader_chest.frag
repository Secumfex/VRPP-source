#version 330 core

//incoming data for the single textures
in vec2 passUVCoords;

uniform sampler2D diffuseTexture;


//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
 
void main(){  


    positionOutput = texture(diffuseTexture, passUVCoords);
}
