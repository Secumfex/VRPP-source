#version 330

in vec2 passUV;

uniform sampler2D positionMap;

out vec4 fragmentColor;

void main() {
    
    
   // vec4 diffuse = texture(positionMap, passUV);

    fragmentColor = diffuse;

}