#version 330

layout(location = 0) in vec2 positionAttribute;
out vec2 passUV;

void main() {
    gl_Position = vec4(positionAttribute, 0, 1);
    passUV = (positionAttribute + 1) / 2;
}