#version 330

layout (location = 0) in vec4 positionAttr
layout (location = 1) in vec4 normalAttr
layout (location = 2) in vec2 uvCoordAttr

uniform mat4 uniModelMat
uniform mat4 uniViewMat
uniform mat4 uniInverse
uniform mat4 uniPerspMat

out vec3 positionPass
out vec3 normalPass
out vec2 uvCoordPass
out vec3 worldPass

void main() {

}