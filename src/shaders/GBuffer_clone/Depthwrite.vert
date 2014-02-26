#version 330 core
 
layout(location = 0) in vec4 positionAttribute;
layout(location = 1) in vec2 uvCoordAttribute;
layout(location = 2) in vec4 normalAttribute;
layout(location = 3) in vec4 tangentAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformProjection;
uniform mat4 uniformLightProjection;

out vec4 passPosition;
out vec2 passUVCoord;


void main(){
    passUVCoord = uvCoordAttribute;
    passPosition = uniformLightProjection * positionAttribute;
    gl_Position = passPosition;
}
