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
#include <map>
#include <sstream>

using namespace std;

/*! @brief ShaderFactory.
 *
 *	the shader factory supports functions for creating and managing Shader entities for certain GraphicsComponent
 */
class ShaderFactory : public Singleton<ShaderFactory> {
friend class Singleton<ShaderFactory>;
public:

/** \brief constructor
*
* Default constructor with no values.
*/
	ShaderFactory();
	/** \brief destructor
		*
		*/
	virtual ~ShaderFactory();
	/** \brief creates GBuffer by GraphicsComponent's flags
	 *
	 * @param GraphicsComponent*
	 * @return Shader*
	 */
	Shader* createGBuffer(GraphicsComponent* gc);
	/** \brief getter
	 *
	 * @return list of shaders created by the factory
	 */
	std::vector<Shader*> getGBuffers();

protected:

	std::string makeKey(GraphicsComponent* gc);
	std::map<std::string, Shader*> mGBufferMap;
	std::vector<Shader*> mGBufferVector;

	std::string createGBuffer_vertex(GraphicsComponent* gc);
	std::string createGBuffer_vertexUniforms(GraphicsComponent* gc);
	std::string createGBuffer_vertexUniforms_bones(GraphicsComponent* gc);
	std::string createGBuffer_vertexNormal(GraphicsComponent* gc);
	std::string createGBuffer_vertex_animation(GraphicsComponent* gc);
	std::string createGBuffer_fragment(GraphicsComponent* gc);
	std::string createGBuffer_fragmentUniforms(GraphicsComponent* gc);
	std::string createGBuffer_fragmentNormal(GraphicsComponent* gc);
	std::string createGBuffer_fragmentColor(GraphicsComponent* gc);

};

#endif /* SHADERFACTORY_H_ */
