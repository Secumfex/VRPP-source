/*
 * GBuffer.h
 *
 *  Created on: 18.02.2014
 *      Author: Dr.M
 */

#ifndef GBUFFER_H_
#define GBUFFER_H_

#include <string>

namespace GBuffer{

std:: string vertexShader ="\
		#version 330 core \n\
		\
layout(location = 0) in vec4 positionAttribute;\
layout(location = 1) in vec2 uvCoordAttribute;\
layout(location = 2) in vec4 normalAttribute;\
layout(location = 3) in vec4 tangentAttribute;\
\
uniform mat4 uniformModel;\
uniform mat4 uniformView;\
uniform mat4 uniformProjection;\
\
out vec4 passPosition;\
out vec2 passUVCoord;\
out vec3 passNormal;\
out vec3 passTangent;\
\
void main(){\
    passUVCoord = uvCoordAttribute;\
\
    passPosition = uniformView * uniformModel * positionAttribute;\
    gl_Position =  uniformProjection * uniformView * uniformModel * positionAttribute;\
\
    passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);\
    passTangent = vec3(transpose(inverse(uniformView * uniformModel)) * tangentAttribute);\
}";
std:: string fragmentShader ="\
		#version 330 core\n\
\
//incoming data for the single textures\
in vec4 passPosition;\
in vec2 passUVCoord;\
in vec3 passNormal;\
\
uniform float shininess;\
\
uniform sampler2D diffuseTexture;\
\
//writable textures for deferred screen space calculations\
layout(location = 0) out vec4 positionOutput;\
layout(location = 1) out vec4 normalOutput;\
layout(location = 2) out vec4 colorOutput;\
layout(location = 3) out vec4 materialOutput;\
 \
void main(){  \
    positionOutput = passPosition;\
    normalOutput = vec4(normalize(passNormal), 0);\
    colorOutput = texture(diffuseTexture, passUVCoord);\
    materialOutput = vec4(shininess, 0.0, 0.0, 0.0);\
}";

}


#endif /* GBUFFER_H_ */
