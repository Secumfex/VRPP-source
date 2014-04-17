#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
 
void main(){  

    positionOutput = passPosition;
    colorOutput = texture(diffuseTexture, passUVCoord);
}
