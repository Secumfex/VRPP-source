#version 330

layout (location = 0) in vec4 positionAttr;
layout (location = 1) in vec2 uvCoordAttr;
layout (location = 2) in vec4 normalAttr;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformInverse;
uniform mat4 uniformPerspective;

out vec3 positions;
out vec3 normals;
out vec2 uvCoords;


void main() {

//gl_Position = uniformPerspective*uniformView*uniformModel*positionAttr;

uvCoords = uvCoordAttr;

positions = (uniformView*uniformModel*positionAttr).xyz;

normals = normalize((uniformInverse*normalAttr).xyz);

}