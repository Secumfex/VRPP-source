#version 330

uniform struct Matrices{ 
   mat4 projMatrix; 
   mat4 modelMatrix; 
   mat4 viewMatrix;                                                                            
   mat4 normalMatrix; 
} matrices; 

layout (location = 0) in vec3 inPosition; 
layout (location = 1) in vec2 inCoord; 
layout (location = 2) in vec3 inNormal; 

out vec2 texCoord; 
out vec3 normal; 
out vec3 worldPos; 
out vec4 eyeSpacePos; 

uniform mat4 heightMapScaleMatrix; 


void main() {

  vec4 inPositionScaled = heightMapScaleMatrix*vec4(inPosition, 1.0); 
  mat4 mvp = matrices.projMatrix*matrices.viewMatrix*matrices.modelMatrix; 
    
  gl_Position = mMVP*inPositionScaled; 
  eyeSpacePos = matrices.viewMatrix*matrices.modelMatrix*vec4(inPosition, 1.0); 
   
  texCoord = inCoord; 
  normal = inNormal; 
    
  vec4 worldPosLocal = matrices.modelMatrix*inPositionScaled; 
  worldPos = worldPosLocal.xyz; 
}