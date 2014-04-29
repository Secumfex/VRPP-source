#version 330

layout (location = 0) in vec4 positionAttribute;
layout (location = 1) in vec2 uvCoordAttribute;
layout (location = 2) in vec4 normalAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformInverse;
uniform mat4 uniformPerspective;

uniform vec3 p0;
uniform vec3 p1;
uniform vec3 p2;
uniform vec3 p3;

out vec2 passUVCoords;

void main() {

	vec3 SavePos = positionAttribute.xyz;
	
//y -> T
//Wir brauchen irgendwie sinnvolles T zwischen 0 und 1, muss es in den 10er Schritten laufen? ggf kann man auch die For Schleife hier rein holen
	float T = SavePos.y/20.0;
	
	float Catmullx =0.5*(T * ((2.0 * p1.x) + ((p2.x - p0.x) * T) + (((2.0 * p0.x) - (5.0 * p1.x) + (4.0 * p2.x) - p3.x) * (T * T))
						+ (((3.0 * p1.x) - p0.x - (3.0 * p2.x) + p3.x) * (T * T * T))));
	float Catmully =0.5* (T * ((2.0 * p1.y) + ((p2.y - p0.y) * T) + ((2.0 * p0.y - 5.0 * p1.y + 4.0 * p2.y - p3.y) * (T * T))
						+ ((3.0 * p1.y - p0.y - 3.0 * p2.y + p3.y) * (T * T * T))));
	float Catmullz =0.5* (T * ((2.0 * p1.z) + ((p2.z - p0.z) * T) + ((2.0 * p0.z - 5.0 * p1.z + 4.0 * p2.z - p3.z) * (T * T))
						+ ((3.0 * p1.z - p0.z - 3.0 * p2.z + p3.z) * (T * T * T))));

    //gl_Position = uniformPerspective * uniformView * uniformModel * positionAttribute;
	gl_Position = uniformPerspective * uniformView * uniformModel * vec4(positionAttribute.x + Catmullx, Catmully, positionAttribute.z + Catmullz, 1);

	vec4 modelPos = ( uniformModel * vec4( 0.0, Catmully, 0.0, 1.0 ) ); 
	vec4 viewPos  = ( uniformView  * modelPos) + ( vec4( positionAttribute.x + Catmullx, 0.0, positionAttribute.z + Catmullz, 0.0 ));
	
	gl_Position = uniformPerspective * viewPos;
	
	passUVCoords = uvCoordAttribute;
}