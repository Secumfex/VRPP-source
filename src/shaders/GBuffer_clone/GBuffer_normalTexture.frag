#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;
in vec3 passTangent;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

uniform float shininess;

//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
layout(location = 3) out vec4 materialOutput;
 
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
    normalOutput = normalize(vec4((tangentSpace * (texture(normalTexture, passUVCoord).rgb * 2.0 - 1.0)), 0.0));
    colorOutput = texture(diffuseTexture, passUVCoord);
    materialOutput = vec4(shininess, 0.0, 0.0, 0.0);
}
