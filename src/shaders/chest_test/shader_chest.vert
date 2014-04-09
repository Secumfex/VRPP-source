#version 330 core
layout (location = 0) in vec4 positionAttribute;
layout (location = 1) in vec2 uvCoordAttribute;


uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformInverse;
uniform mat4 uniformPerspective;


out vec2 passUVCoords;


void main() {

    gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;


    
    passUVCoords = uvCoordAttribute;
}