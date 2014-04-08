#version 330

layout (location = 0) in vec4 positionAttribute;
//layout (location = 1) in vec2 uvCoordAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;

uniform float uniformScale;

uniform float uniformSinus;

out vec2 passUVCoords;
out float passDistance;

void main() {
   
//	gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;   
//  gl_Position =  uniformPerspective * ( positionAttribute + vec4 ( uniformView[3].xyz, 0.0));
//	gl_Position = uniformPerspective * ( ( uniformModel * positionAttribute )  + vec4( uniformView[3].xyz, 0.0) );
	vec4 modelPos = ( uniformModel * vec4( uniformSinus * 0.5, 0.0, uniformSinus * 0.5, 1.0 ) ); 
	vec4 viewPos  = ( uniformView  * modelPos)- ( vec4( positionAttribute.x, positionAttribute.y, 0.0, 0.0 ) * uniformScale) ;
	
	passDistance = viewPos.z;

	gl_Position = uniformPerspective * viewPos;
   
	passUVCoords = vec2( positionAttribute.x + 0.5, positionAttribute.y + 0.5);

}