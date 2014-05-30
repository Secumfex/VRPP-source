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
class VirtualObject;

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
	bool mInvertCondition;
public:
	RenderQueueRequestFlag();

	/*! @brief setter
	 * @param to boolean whether condition should be inverted to be true
	 */
	void setInvertCondition(bool to);
	
	/*! @brief getter
	 * @return boolean whether condition should be inverted to be true 
	 */
	bool getInvertCondition();

	/*! @brief Send flag-objects to the RenderQueue
	 *
	 * Abstract method, sends Flag objects to overloaded metods ín the RenderQueue
	 */
	virtual list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp) = 0;
};

/*! @brief flag-child 
 *
 * A flag for a shadow casting render pass
 */
class FlagShadowCaster : public RenderQueueRequestFlag{
private:
public:
	FlagShadowCaster(bool invertedCondition = false);

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
	FlagUsesShader(Shader* shader, bool invertedCondition = false);

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag : graphics component uses mesh object
 *
 * A flag for using a certain object model, true for a graphics component
 * if its Mesh is equal to the provided reference mesh
 */
class FlagUsesMesh : public RenderQueueRequestFlag{
private:
	Mesh* mMesh;
public:
	FlagUsesMesh(Mesh* mesh, bool invertedCondition = false);

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

/*! @brief flag : graphics component uses mesh object
 *
 * A flag for using a certain object model, true for a graphics component
 * if its Mesh is equal to the provided reference mesh
 */
class FlagPartOfVirtualObject : public RenderQueueRequestFlag{
private:
	VirtualObject* mVO;
public:
	FlagPartOfVirtualObject(VirtualObject* vo, bool invertedCondition = false);

	VirtualObject* getVirtualObject();
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
	FlagInViewFrustum(bool invertedCondition = false);

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
	FlagTransparency(bool invertedCondition = false);

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
	FlagScreenFillingPolygon(bool invertedCondition = false);

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

class CurrentRenderQueueFlag : public RenderQueueRequestFlag{
private:
public:
	CurrentRenderQueueFlag(bool invertedCondition = false);

	/*! @brief flag visits the render queue
	 *
	 * flag sends itself to the render queue, which will trigger the overloaded method
	 */
	list<GraphicsComponent* > extrudeGCsRequestFlagList(RenderQueue* rq, list<GraphicsComponent* > temp);
};

#endif
