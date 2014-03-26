/*
 * ShaderFactory.cpp
 *
 *  Created on: 18.03.2014
 *      Author: Dr.M
 */

#include "Tools/ShaderFactory.h"

ShaderFactory::ShaderFactory() {
	// TODO Auto-generated constructor stub

}

ShaderFactory::~ShaderFactory() {
	// TODO Auto-generated destructor stub
}

Shader* ShaderFactory::createGBuffer(GraphicsComponent* gc){

	std::string key = makeKey(gc);

	if(mGBufferMap.find(key) != mGBufferMap.end())
		return mGBufferMap[key];

	std::string vert = createGBuffer_vertex(gc);
	std::string frag = createGBuffer_fragment(gc);


	std::vector<const char*> shaders;
	shaders.push_back(vert.c_str());
	shaders.push_back(frag.c_str());

	cout << shaders[0] << endl;
	//	cout << shaders[1] << endl;

	Shader* shader = new Shader(shaders);

	mGBufferMap.insert(std::pair<std::string, Shader*>(key, shader));
	mGBufferVector.push_back(shader);

	return shader;
}

std::string ShaderFactory::createGBuffer_vertex(GraphicsComponent* gc){
	std::string vert = "\
#version 330 core\n\
\n\
			";
	vert += createGBuffer_vertexUniforms(gc);
	vert += "\
void main(){\n\
passUVCoord = uvCoordAttribute;\n\
passPosition = uniformView * uniformModel *";

	vert += createGBuffer_vertex_animation(gc);

	vert +=	"positionAttribute;\n\
gl_Position =  uniformPerspective * uniformView * uniformModel * ";

	vert += createGBuffer_vertex_animation(gc);

	vert +=			"positionAttribute;\n\
";
	vert += createGBuffer_vertexNormal(gc);

	vert += "\
\n\
}\n\
			";

	return vert;
}
std::string ShaderFactory::createGBuffer_fragment(GraphicsComponent* gc){
	std::string frag = "\
#version 330 core\n\
\n\
			";

	frag += createGBuffer_fragmentUniforms(gc);
	frag +="\
//writable textures for deferred screen space calculations\n\
layout(location = 0) out vec4 positionOutput;\n\
layout(location = 1) out vec4 normalOutput;\n\
layout(location = 2) out vec4 colorOutput;\n\
layout(location = 3) out vec4 specularOutput;\n\
\n\
void main(){\n\
";
	frag += createGBuffer_fragmentNormal(gc);
	frag += createGBuffer_fragmentColor(gc);

	frag += "\
positionOutput = passPosition;\n\
specularOutput = vec4(specularColor, shininess);\n\
\n\
}\n\
			";

	return frag;
}

std::string ShaderFactory::createGBuffer_vertexUniforms(GraphicsComponent* gc){
	std::string vertexUniforms = "\n\
layout(location = 0) in vec4 positionAttribute;\n\
layout(location = 1) in vec2 uvCoordAttribute;\n\
layout(location = 2) in vec4 normalAttribute;\n\
layout(location = 3) in vec4 tangentAttribute;\n\
";

	vertexUniforms+= createGBuffer_vertexUniforms_bones(gc);
	vertexUniforms += "\
uniform mat4 uniformModel;\n\
uniform mat4 uniformView;\n\
uniform mat4 uniformPerspective;\n\
out vec4 passPosition;\n\
out vec2 passUVCoord;\n\
out vec3 passNormal;\n\
";

	if (gc->getMaterial()->hasNormalTexture()){
		vertexUniforms += "\
out vec3 passTangent;\n\
\n\
";
	}

	return vertexUniforms;
}
std::string ShaderFactory::createGBuffer_fragmentUniforms(GraphicsComponent* gc){
	std::string vertexUniforms = "\n\
in vec4 passPosition;\n\
in vec2 passUVCoord;\n\
in vec3 passNormal;\n\
\n\
uniform float shininess;\n\
uniform vec3 specularColor;\n\
\n\
"
			;
	if (gc->getMaterial()->hasNormalTexture())
		vertexUniforms += "\
in vec3 passTangent;\n\
\n\
";

	if (gc->getMaterial()->hasDiffuseTexture())
		vertexUniforms += "\
uniform sampler2D diffuseTexture;\n\
\n\
"; else
	vertexUniforms += "\
uniform vec3 diffuseColor;\n\
\n\
";
	if (gc->getMaterial()->hasNormalTexture())
		vertexUniforms += "\
uniform sampler2D normalTexture;\n\
\n\
";

	return vertexUniforms;
}
std::string ShaderFactory::createGBuffer_vertexNormal(GraphicsComponent* gc){
	if(gc->getMaterial()->hasNormalTexture())
		return "\
passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);\n\
passTangent = vec3(transpose(inverse(uniformView * uniformModel)) * tangentAttribute);\n\
";
	else
		return "\
passNormal = vec3(transpose(inverse(uniformView * uniformModel)) * normalAttribute);\n\
";
}
std::string ShaderFactory::createGBuffer_fragmentNormal(GraphicsComponent* gc){

	std::string fragmentNormal;

	if(gc->getMaterial()->hasNormalTexture())
		fragmentNormal = "\
vec3 normal = normalize(passNormal.xyz);\n\
vec3 tangent = normalize(passTangent.xyz);\n\
vec3 binormal = cross(tangent, normal);\n\
\n\
mat3 tangentSpace = mat3(\n\
tangent.x, tangent.y, tangent.z,\n\
binormal.x, binormal.y, binormal.z,\n\
normal.x, normal.y, normal.z\n\
);\n\
normalOutput = normalize(vec4((tangentSpace * (texture(normalTexture, passUVCoord).rgb * 2.0 - 1.0)), 0.0));\n\
\n\
";
	else
		fragmentNormal = "\
normalOutput = vec4(normalize(passNormal), 0);\n\
\n\
";

	return fragmentNormal;
}
std::string ShaderFactory::createGBuffer_fragmentColor(GraphicsComponent* gc){
	if(gc->getMaterial()->hasDiffuseTexture())
		return "\
colorOutput = texture(diffuseTexture, passUVCoord);\n\
";
	else
		return "\
colorOutput = vec4(diffuseColor,0);\n\
";
}

std::string ShaderFactory::makeKey(GraphicsComponent* gc){
	std::string key = "gbuffer";

	if(gc->getMaterial()->hasDiffuseTexture())
		key += "_difftex_";
	if(gc->getMaterial()->hasNormalTexture())
		key += "_nrmtex_";
	if(gc->getMaterial()->hasShininessTexture())
		key += "_shinitex_";
	if(gc->getMaterial()->hasSpecularTexture())
		key += "_spectex_";
	if(gc->hasAnimation()){
		key += "_bones_";
		key += static_cast<ostringstream*>( &(ostringstream() << gc->getBones().size()) )->str();
		key += "_";
	}



	return key;
}

std::vector<Shader*> ShaderFactory::getGBuffers(){
	return mGBufferVector;
}

std::string ShaderFactory::createGBuffer_vertexUniforms_bones(GraphicsComponent* gc){
	std::string vertexUniforms = "";
	if(gc->hasAnimation()){
		vector<Bone*> bones = gc->getBones();
		unsigned int i;
		for (i = 0; i < bones.size(); ++i) {
			ostringstream convert_loc;
			ostringstream convert_index;
			convert_loc << (i +10);
			convert_index << i;

			vertexUniforms += "layout(location = ";
			vertexUniforms += convert_loc.str();
			vertexUniforms += ") in float boneWeight";
			vertexUniforms += convert_index.str();
			vertexUniforms += ";\n";
		}
		vertexUniforms += "\n";
		for (i = 0; i < bones.size(); ++i){
			ostringstream convert_index;
			convert_index << i;
			vertexUniforms += "uniform mat4 ";
			vertexUniforms += "uniformBoneTransform";
			vertexUniforms += convert_index.str();
			vertexUniforms += ";\n";
		}
	}
	return vertexUniforms;
}

std::string ShaderFactory::createGBuffer_vertex_animation(GraphicsComponent* gc){
	std::string boneTransforms = "";

	if(gc->hasAnimation()){
		unsigned int i;
		vector<Bone*> bones = gc->getBones();
			boneTransforms += " ( ";
		for (i = 0; i < bones.size(); ++i) {
			ostringstream convert_index;
			convert_index << i;
			boneTransforms += " (uniformBoneTransform";
			boneTransforms += convert_index.str();
			boneTransforms += " * boneWeight";
			boneTransforms += convert_index.str();
			boneTransforms += " ) ";

			if(i != (bones.size() - 1))
			boneTransforms += " + ";
		}

			boneTransforms += " ) * ";

	}

	return boneTransforms;

}
