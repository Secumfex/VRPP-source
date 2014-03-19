#ifndef RENDERQUEUEREQUESTFLAG_H
#define RENDERQUEUEREQUESTFLAG_H

//#include "RenderQueue.h"
#include "Patterns/Visitor.h"
#include <list>

using namespace std;

/*! @brief Proxyclass for forward including
 *
 *
 */
class Shader;

/*! @brief Proxyclass for forward including
 *
 *
 */
class Mesh;

/*! @brief Proxyclass for forward including
 *
 *
 */
class GraphicsComponent;

/*! @brief Proxyclass for forward including
 *
 *
 */
class RenderQueue;

/*! @brief Proxyclass for forward including
 *
 *
 */
class GrapicsComponent;

/*! @brief Proxyclass for forward including
 *
 *
 */
class Shader;

/*! @brief Parent flag-class
 *
 * Other flags will be derived from this class
 */
class RenderQueueRequestFlag{
private:
public:
	/*! @brief Send flag-objects to the RenderQueue
	 *
	 * Abstract method, sends Flag objects to overloaded metods ín the RenderQueue
	 */
	virtual list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag-child 
 *
 * A flag for a shadow casting render pass
 */
class FlagShadowCaster : public RenderQueueRequestFlag{
private:
public:
	FlagShadowCaster();

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag-child
 *
 * A flag for using a certain shader
 */
class FlagUsesShader : public RenderQueueRequestFlag{
private:
	Shader* mShader;
public:
	FlagUsesShader(Shader* shader);

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag-child
 *
 * A flag for using a certain object model
 */
class FlagUsesObjectModel : public RenderQueueRequestFlag{
private:
	Mesh* mMesh;
public:
	FlagUsesObjectModel(Mesh* mesh);

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag-child
 *
 * A flag for objects within the view frustum
 */
class FlagInViewFrustum : public RenderQueueRequestFlag{
private:
public:
	FlagInViewFrustum();

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag-child
 *
 * A flag for transparent objects
 */
class FlagTransparency : public RenderQueueRequestFlag{
private:
public:
	FlagTransparency();

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag-child
 *
 * A flag for the screen filling triangle
 */
class FlagScreenFillingPolygon : public RenderQueueRequestFlag{
private:
public:
	FlagScreenFillingPolygon();

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

#endif