#version 330 core

//incoming data for the single textures
in vec4 passPosition;
in vec2 passUVCoord;
in vec3 passNormal;
in vec3 passTangent;

uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

//writable textures for deferred screen space calculations
layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
 
void main(){  

	vec3 normal = normalize((uniformNormal * normalAttribute).xyz);
    vec3 tangent = normalize((uniformNormal * tangentAttribute).xyz);
    vec3 binormal = cross(tangent, normal);

		mat3 tangentSpace = mat3(
        tangent.x, binormal.x, normal.x,
        tangent.y, binormal.y, normal.y,
        tangent.z, binormal.z, normal.z
    );

    positionOutput = passPosition;
    normalOutput = normalize(texture(normalTexture, passUVCoord));
    colorOutput = texture(diffuseTexture, passUVCoord);
}
