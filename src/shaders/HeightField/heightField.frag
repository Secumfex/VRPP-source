#version 330 

smooth in vec2 texCoord; 
smooth in vec3 normal; 
smooth in vec3 worldPos; 
smooth in vec4 eyeSpacePos; 

uniform sampler2D sampler[5]; 
uniform sampler2D shadowMap; 

uniform vec4 color; 
uniform float renderHeight; 

out vec4 outputColor;

void main() { 

   vec3 normalized = normalize(normal); 
    
   vec4 texColor = vec4(0.0); 
    
   float scale = worldPos.y/renderHeight; 

   const float range1 = 0.15f; 
   const float range2 = 0.30f; 
   const float range3 = 0.65f; 
   const float range4 = 0.85f; 

   if(scale >= 0.0 && scale <= range1){
   	  	texColor = texture2D(gSampler[0], vTexCoord); 
   }
   else if(scale <= range2){ 
      	scale -= range1; 
      	scale /= (range2-range1); 
       
      	float scale2 = scale; 
      	scale = 1.0-scale;  
       
     	 texColor += texture2D(sampler[0], texCoord)*scale; 
      	texColor += texture2D(sampler[1], texCoord)*scale2; 
   } 
   else if(scale <= range3){
   		texColor = texture2D(sampler[1], texCoord); 
   }
   else if(scale <= range4){ 
      	scale -= range3; 
     	scale /= (range4-range3); 
       
      	float scale2 = scale; 
      	scale = 1.0-scale;  
       
      	texColor += texture2D(sampler[1], texCoord)*scale; 
      	texColor += texture2D(sampler[2], texCoord)*scale2;       
   } 
   else{
    	texColor = texture2D(sampler[2], texCoord);
   }
   outputColor = scale*texColor+(1-scale)*color; 
}