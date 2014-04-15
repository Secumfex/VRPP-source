#version 330 

in vec3 normalPass;
in vec3 positionPass;
in vec2 uvCoordPass;

uniform sampler2D uniformTexture1;
uniform sampler2D uniformTexture2;
uniform sampler2D uniformTextureMask;

uniform sampler2D uniformNormals1;
uniform sampler2D uniformNormals2;

uniform sampler2D uniformSpecular1;
uniform sampler2D uniformSpecular2;

layout(location = 0) out vec4 positionOut;
layout(location = 1) out vec4 colorOut;
layout(location = 2) out vec4 normalOut;
layout(location = 3) out vec4 specularOut;


void main() { 

positionOut = positionPass;

vec4 color1 = texture2D(uniformTexture1,uvCoordPass);
vec4 color2 = texture2D(uniformTexture2,uvCoordPass);
vec4 mask = texture2D(uniformTextureMask,uvCoordPass);

//gl_FragColor = mix(color1,color2,mask.r);
colorOut = mix(color1,color2,mask.r);

vec4 normals1 = texture2D(uniformNormals1,uvCoordPass);
vec4 normals2 = texture2D(uniformNormals2,uvCoordPass);

normalOut = mix(normals1,normals2,mask.r);

vec4 specular1 = texture2D(uniformSpecular1,uvCoordPass);
vec4 specular2 = texture2D(uniformSpecular2,uvCoordPass);

specularOut = mix(specular1,specular2,mask.r);

//normals mit maske und in fbo
//normals normalisieren
//phong mit normals

//selbe mit glossmaps
}