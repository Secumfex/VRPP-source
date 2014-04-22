#version 330 core
 
layout(location = 0) in vec4 positionAttribute;
layout(location = 1) in vec2 uvCoordAttribute;
layout(location = 2) in vec4 normalAttribute;
layout(location = 3) in vec4 tangentAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;

out vec4 passPosition;
out vec2 passUVCoord;
out vec3 passNormal;
out vec3 passTangent;



void main(){
    passUVCoord = uvCoordAttribute;

    passPosition = uniformView * uniformModel * positionAttribute;
    gl_Position =  uniformPerspective * uniformView * uniformModel * positionAttribute;

    passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);
    passTangent = vec3(transpose(inverse(uniformView * uniformModel)) * tangentAttribute);
}
