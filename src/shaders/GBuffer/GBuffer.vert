#version 330 core
 
layout(location = 0) in vec4 positionAttribute;
layout(location = 1) in vec2 uvCoordAttribute;
layout(location = 2) in vec4 normalAttribute;

uniform mat4 uniformModel;
uniform mat4 uniformView;
uniform mat4 uniformPerspective;

out VertexData {
	vec4 Position;
	vec2 UVCoord;
	vec3 Normal;
} VertexOut;

//out vec4 passPosition;
//out vec2 passUVCoord;
//out vec3 passNormal;

 
void main(){
    //passUVCoord = uvCoordAttribute;
    VertexOut.UVCoord = uvCoordAttribute;

    //passPosition = uniformView * uniformModel * positionAttribute;
    VertexOut.Position = uniformView * uniformModel * positionAttribute;
    gl_Position =  uniformPerspective * uniformView * uniformModel * positionAttribute;

    //passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);
    VertexOut.Normal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);
}
