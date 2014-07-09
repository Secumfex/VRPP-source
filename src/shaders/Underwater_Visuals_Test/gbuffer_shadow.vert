#version 330

layout (location = 0) in vec4 positionAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;

void main() {
    gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;
}