/*
 * ShaderFactory.h
 *
 *  Created on: 18.03.2014
 *      Author: Dr.M
 */

#ifndef SHADERFACTORY_H_
#define SHADERFACTORY_H_

#include <Patterns/Singleton.h>
#include <Visuals/Shader.h>
#include <Visuals/GraphicsComponent.h>

class ShaderFactory : public Singleton<ShaderFactory> {
friend class Singleton<ShaderFactory>;
public:
	ShaderFactory();
	virtual ~ShaderFactory();

	Shader* createGBuffer(GraphicsComponent* gc);

protected:
	std::string createGBuffer_vertex(GraphicsComponent* gc);
	std::string createGBuffer_fragment(GraphicsComponent* gc);
	std::string createGBuffer_vertexUniforms(GraphicsComponent* gc);
	std::string createGBuffer_fragmentUniforms(GraphicsComponent* gc);
	std::string createGBuffer_vertexNormal(GraphicsComponent* gc);
	std::string createGBuffer_fragmentNormal(GraphicsComponent* gc);
	std::string createGBuffer_fragmentColor(GraphicsComponent* gc);

};

#endif /* SHADERFACTORY_H_ */