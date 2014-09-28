#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

//in vec4 passPosition;
//in vec2 passUVCoord;
//in vec3 passNormal;

out vec4 passPosition;
out vec2 passUVCoord;
out vec3 passNormal;

in VertexData {
 vec4 Position;
 vec2 UVCoord;
 vec3 Normal;
} VertexIn[3];

out VertexData {
 vec4 Position;
 vec2 UVCoord;
 vec3 Normal;
} VertexOut;

void main(){

 for (int i=0; i<gl_in.length(); i++){
 gl_Position = gl_in[i].gl_Position;

 passPosition = VertexIn[i].Position;
 passNormal = VertexIn[i].Normal;
 passUVCoord = VertexIn[i].UVCoord;

 EmitVertex();
 }

 EndPrimitive();

}