#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;
in vec3 passTangent;
//in vec3 vVaryingLightDir;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;
uniform vec3 specularColor;

uniform float shininess;

//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
layout(location = 3) out vec4 specularOutput;

void main(){
    
	vec3 normal = normalize(passNormal.xyz);
    vec3 tangent = normalize(passTangent.xyz);
    vec3 binormal = cross(tangent, normal);
    
    mat3 tangentSpace = mat3(
                             tangent.x, tangent.y, tangent.z,
                             binormal.x, binormal.y, binormal.z,
                             normal.x, normal.y, normal.z
                             );
    
    
    positionOutput = passPosition;
    normalOutput = normalize(vec4((tangentSpace * (texture(normalTexture, passUVCoord).rgb - 0.5 ) * 2.0), 0.0));
    colorOutput = texture(diffuseTexture, passUVCoord);
    specularOutput = vec4(specularColor, shininess);
}
