#version 330

in vec3 position;
in vec3 normal;

struct LightInfo {
	vec4 pos;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	};
	
uniform LightInfo Light;

struct MaterialInfo {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
	};
	
uniform MaterialInfo Material;
uniform vec4 sceneAmbient;

out vec4 fragColor;

void main() {
	// ambient component
	fragColor = (sceneAmbient * Material.ambient) + (Light.ambient * Material.ambient);
	vec3 l = normalize(vec3(Light.pos) - position); 
	
	vec3 n = normalize(normal);
	float lDotN = max(dot(l, n), 0.0);
	
	if(lDotN > 0.0) { // if lDotN is zero, there is no light reaching the surface
	// diffuse component
	fragColor += Light.diffuse * Material.diffuse * lDotN;
	
	// specular component
	vec3 v = normalize(vec3(-position)); // in viewspace camera is at origin, so this is the view-vector 
	vec3 r = reflect(-l, n);
	fragColor += Light.specular * Material.specular * pow( max( dot(r, v), 0.0), Material.shininess);
	}
}