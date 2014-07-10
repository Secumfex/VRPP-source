#version 330

in vec2 passUV;

uniform sampler2D preGlowTexture;
uniform sampler2D colorMap;

uniform float resX;
uniform float resY;

out vec4 fragmentColor;

void main() {
	int strength = 8;

	float resX_temp = 1.0/resX;
    float resY_temp = 1.0/resY;

	vec4 glow = vec4(0,0,0,1);
    for(int i = -strength; i < strength; i++) {
        for(int j = -strength; j < strength; j++) {
            vec4 c = texture(colorMap, passUV + vec2(resX_temp * i * 1, resY_temp * j * 1));
            if(c.r + c.g + c.b > 1.5) {                
                glow += c;
            }
        }
    }
    glow /= strength * strength * 4;
    fragmentColor = texture(preGlowTexture, passUV);
    fragmentColor += glow;
}