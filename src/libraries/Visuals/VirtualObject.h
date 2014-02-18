#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"

#include <glm/glm.hpp>
#include <vector>


class VirtualObject{

	private:
	glm::mat4 modelMatrix;							/**< 4x4Matrix */
	int id;											/**< identification number */

	vector<GraphicsComponent*> mGraphComponent;		/**< vector of graphic-components */

public:

//	vector<GraphicsComponent> graphicsComponent;	/**< pointer to the graphics Component of the VO*/

	/** \brief constructor
	 *
	 * void constructor, sets modelMatrix to zero, sets the id to last id+1 and creates a new physicsComponent.
	 */
	VirtualObject();

	/** \brief constructor
	 *
	 * if you know a modelMAtrix you can start with this constructor.
	 * it sets modelMatrix to the given one, sets the id to last id+1  and creates a new physicsComponent.
	 * @param modelMatrix 4x4Matrix
	 */
	VirtualObject(glm::mat4 modelMatrix);

	/** \brief destructor
	 *
	 * deletes the physics and graphics components
	 */
	~VirtualObject();

	/** \brief updates the modelMatrix
	 *
	 * fetches the current modelMatrix of the physicsComponent
	 */
	void updateModelMatrix();
	
	/** \brief
	*
	* 	@todo detailed description
	*/
	void addGraphicsComponent(GraphicsComponent *graphcomp);

	vector<GraphicsComponent*> getGraphicsComponent();

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with no values (default Constructor of PhysicsComponent class)
	 */
	void setPhysicsComponent();

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with given modelmatrix
	 */
	void setPhysicsComponent(glm::mat4 modelMatrix);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent (box shaped rigid Body)
	 * @param modelmatrix given modelmatrix of VO
	 */
	void setPhysicsComponent(glm::vec3 min, glm::vec3 max);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent (sphere shaped rigid Body)
	 * @param radius dimension of the sphere
	 * @param x,y,z origin position in physics world
	 * @mass defines the behavior of the rigid body in the physics world
	 */
	void setPhysicsComponent(float radius, float x, float y, float z, float mass);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent (box shaped rigid Body)
	 * @param width,height,depth dimension of the box
	 * @param x,y,z origin position in physics world
	 * @mass defines the behavior of the rigid body in the physics world
	 */
	void setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass);			//TODO: Dokumentation

	glm::mat4 getModelMatrix();

	void setModelMatrix(glm::mat4 modelmatrix);

	PhysicsComponent *physicsComponent; 			/**< pointer to the physics component of the VO */

	PhysicsComponent* getPhysicsComponent();
};


#endif /* VIRTUALOBJECT_H */
