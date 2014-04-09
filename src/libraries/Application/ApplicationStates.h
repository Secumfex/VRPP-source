#ifndef APPLICATIONSTATES_H
#define APPLICATIONSTATES_H

#include <string.h>
#include <glm/glm.hpp>

#include "Patterns/State.h"
#include "Patterns/Subject.h"
#include "IO/IOHandler.h"
#include "Visuals/VirtualObjectFactory.h"
#include "Visuals/Frustum.h"

class Camera; class RenderQueue; class VirtualObject;

/// Base class of States specifically for the Application-Class
class ApplicationState : public State{


protected: 
	/*Member variables*/
	Frustum* frustum;				/**< frustum associated with camera, used for frustum culling */
	Camera* camera;					/**< camera to be used for view in this state */
	RenderQueue* renderQueue;		/**< renderqueue to be used for rendering in this state */
	IOHandler* iOHandler;			/**< IOHandler to be used for input interpretation */
	glm::mat4 perspectiveMatrix;	/**< perspective matrix to be used by rendering! */

	/** \brief bind objects to RenderManager, IOManager, PhysicsWorld etc.
	 *	
	 */
	virtual void bindObjects();
public:
	/** \brief constructor
	 *
	 */
	ApplicationState();

	/** \brief getter
	 *
	 * @return frustum
	 */
	Frustum*		getFrustum();

	/** \brief getter
	 *
	 * @return camera
	 */
	Camera* 		getCamera();

	/** \brief getter
	 *
	 * @return renderQueue
	 */
	RenderQueue* 	getRenderQueue();

	/** \brief getter
	 *
	 * @return iOHandler
	 */
	IOHandler* 		getIOHandler();

	/** \brief getter
	 *
	 * @return perspectiveMatrix
	 */
	glm::mat4 		getPerspectiveMatrix();

	/** \brief setter
	 *
	 * @param camera
	 */
	void setCamera(				Camera* camera);

	/** \brief setter
	 *
	 * @param renderQueue
	 */
	void setRenderQueue(		RenderQueue* renderQueue);

	/** \brief setter
	 *
	 * @param iOHandler
	 */
	void setIOHandler(			IOHandler* iOHandler);


	/** \brief setter
	 *
	 * @param projectionMatrix
	 */
	void setPerspectiveMatrix(	glm::mat4 projectionMatrix);

	/** \brief activation of state --> binding objects
	 *
	 */
	virtual void activate();

	/** \brief create Object from path and add it to renderQueue
	 *
	 * @param path
	 * @param bodyType
	 * @param mass
	 * @param collisionFlag
	 * @param blenderAxes
	 * @return VirtualObject reference
	 */
	VirtualObject* createVirtualObject(std::string path, VirtualObjectFactory::BodyType bodyType = VirtualObjectFactory::OTHER, float mass = 0.0, int collisionFlag = 1, bool blenderAxes = false); //!< create Object from path and add it to renderQueue

	/** \brief add existing VO to renderQueue
	 *
	 * @param vo
	 */
	void addVirtualObject(VirtualObject* vo);




	/*Application State Listeners*/
	/** \brief attach listener
	 *
	 * attach Listener on Activation
	 * @param listener
	 */
	void attachListenerOnActivation(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on binding objects
	 * @param listener
	 */
	void attachListenerOnBindingObjects(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on creating a new object
	 * @param listener
	 */
	void attachListenerOnCreatingVirtualObject(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on adding a new object
	 * @param listener
	 */
	void attachListenerOnAddingVirtualObject(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on button press or button release
	 * @param listener
	 */
	void attachListenerOnButton(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on beginning Program Cycle
	 * @param listener
	 */
	void attachListenerOnBeginningProgramCycle(Listener* listener);
};

/// An ApplicationState with no added functionality
class IdleState : public ApplicationState {
};

/// An  ApplicationState supposed to contain a mouse click enabled IOHandler
class MenuState : public ApplicationState {
public:
	/** \brief constructor
	 *
	 */
	MenuState(std::string name = "");
};

/// An ApplicationState supposed to contain a Camera Movement enabled IOHandler
class VRState : public ApplicationState {
public:
	/** \brief constructor
	 *
	 */
	VRState(std::string name = "");

	/** \brief activate the VR-State
	 *
	 */
	void activate();
};
#endif
