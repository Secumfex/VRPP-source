#version 330

layout (location = 0) in vec4 positionAttribute;
//layout (location = 1) in vec2 uvCoordAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;

// uniform vec3 uniformParticlePosition;

out vec2 passUVCoord;

void main() {
   
	gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;   
 //  gl_Position =  uniformPerspective * ( positionAttribute + vec4 ( uniformView[3].xyz, 0.0));
//	gl_Position = uniformPerspective * ( ( positionAttribute + vec4 ( uniformModel[3].xyz, 0.0) + vec4( uniformView[3].xyz) ) );
	passUVCoord = vec2( positionAttribute.x + 0.5, positionAttribute.y + 0.5);
}