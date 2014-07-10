#version 330

layout (location = 0) in vec4 positionAttribute;

uniform mat4 uniformModel;			// object model matrix
uniform mat4 uniformView;			// sun view matrix
uniform vec3 uniformCameraWorldPos; // camera position
uniform mat4 uniformPerspective;	

void main() {
	// subtract camera position, to have the shadow map move with the camera
    gl_Position = uniformPerspective * uniformView * ( ( uniformModel * positionAttribute ) - vec4( uniformCameraWorldPos, 0 ) );
//    gl_Position = uniformPerspective * uniformView * ( uniformModel * positionAttribute );

}