#version 330

layout (location = 0) in vec4 positionAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;
uniform mat4 uniformProjectorViewPerspective;

uniform vec3 uniformLightPosition;

out vec3 passWorldPos;
out vec4 passProjectedPos;

void main() {
	passWorldPos     = (uniformModel * positionAttribute).xyz;
    passProjectedPos = uniformProjectorViewPerspective * positionAttribute;
    
    gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;

}