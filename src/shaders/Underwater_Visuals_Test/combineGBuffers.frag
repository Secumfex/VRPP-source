#version 330

in vec2 passUV;

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D colorMap;

uniform sampler2D positionMap_2;
uniform sampler2D normalMap_2;
uniform sampler2D colorMap_2;

layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;

void main() {
	vec4 position = texture(positionMap, passUV);	 //GBUFFER
	vec4 position2 = texture(positionMap_2, passUV); //SKY
	
	vec4 color = texture(colorMap, passUV);
	vec4 normal =texture(normalMap, passUV);
	
	if ( ( abs ( position.z ) > abs ( position2.z ) ) && position2.z != 0.0 || ( position.z == 0.0 ) )	// position 2 is in front
	{
		position = position2;
		color = texture( colorMap_2, passUV);
		normal = texture(normalMap_2, passUV);
	}
	
    colorOutput = color;
    normalOutput = normal;
    positionOutput = position;

}