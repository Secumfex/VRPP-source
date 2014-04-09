#version 330

layout (location = 0) in vec4 positionAttr;
layout (location = 1) in vec2 uvCoordAttr;
layout (location = 2) in vec4 normalAttr;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformInverse;
uniform mat4 uniformPerspective;

out vec3 positionPass;
out vec3 normalPass;
out vec2 uvCoordPass;
out vec3 worldPass;

void main() {

gl_Position = uniformPerspective*uniformView*uniformModel*positionAttr;

uvCoordPass = uvCoordAttr;

positionPass = (uniformView*uniformModel*positionAttr).xyz;

normalPass = normalize((uniformInverse*normalAttr).xyz);

}