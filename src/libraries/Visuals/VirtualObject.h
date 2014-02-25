#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"

#include <glm/glm.hpp>
#include <vector>


class VirtualObject{

	private:
	glm::mat4 modelMatrix;							/**< 4x4Matrix */										/**< identification number */

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

	/** \brief constructor
	 *
	 * creates VirtualObject with min and max vector of the mesh
	 * creates physicComponent with same vectors
	 * @param min,max glm::vec3 vector for max an min x,y and z values
	 */
	VirtualObject(glm::vec3 min, glm::vec3 max);

	/** \brief constructor
	 *
	 * creates a sphere as virtual object
	 * creates physicComponent as a sphere as well
	 * @param radius radius of sphere
	 * @param x,y,z position of sphere
	 * @param mass mass of the rigidBody (physicComponent)
	 */
	VirtualObject(float radius, float x, float y, float z, float mass);

	/** \brief constructor
	 *
	 * creates a box as virtual object
	 * creates physicComponent as a box as well
	 * @param width,height,depth size of the box
	 * @param x,y,z position of box
	 * @param mass mass of the rigidBody (physicComponent)
	 */
	VirtualObject(float width, float height, float depth, float x, float y, float z, float mass);

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
	* adds a GraphicComponent to the VOs graphic component vector "mGraphComponent"
	* @param graphcomp GraphicComponent pointer
	* @return void
	*/
	void addGraphicsComponent(GraphicsComponent *graphcomp);

	/** \brief getter
	*
	* return the current graphic component vector
	* @return the VOs graphic component vector "mGraphComponent"
	*/
	vector<GraphicsComponent*> getGraphicsComponent();

	vector<GraphicsComponent*> getGraphicsComponent(std::string tag);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with no values (default Constructor of PhysicsComponent class)
	 */
	void setPhysicsComponent();

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with given modelMatrix
	 * @param modelMatrix 4x4-matrix
	 * @return void
	 */
	void setPhysicsComponent(glm::mat4 modelMatrix);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with box shaped rigid Body
	 * @param min,max smallest and largest x, y, z values of a given model
	 * @return void
	 */
	void setPhysicsComponent(glm::vec3 min, glm::vec3 max);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with sphere shaped rigid Body
	 * @param radius dimension of the sphere
	 * @param x,y,z origin position in physics world
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return void
	 */
	void setPhysicsComponent(float radius, float x, float y, float z, float mass);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with box shaped rigid Body
	 * @param width,height,depth dimension of the box
	 * @param x,y,z origin position in physics world
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return void
	 */
	void setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with plane shaped rigid Body
 	 * @param x,y,z origin position in physics world
 	 * @param normal normal vector of the plane
 	 * @param mass defines the behavior of the rigid body in the physics world
 	 * @return void
	 */
	void setPhysicComponent(float x, float y, float z, btVector3 normal, float mass);	//todo: change the type of normal

	/** \brief getter
	 *
	 * returns current modelMatrix
	 * @return glm::mat4 4x4-matrix
	 */
	glm::mat4 getModelMatrix();

	/** \brief setter
	 *
	 * sets a given matrix as the VOs modelMatrix
	 * @param modelmatrix 4x4-matrix
	 * @return void
	 */
	void setModelMatrix(glm::mat4 modelmatrix);

	PhysicsComponent *physicsComponent; 			/**< pointer to the physics component of the VO */

	PhysicsComponent* getPhysicsComponent();
};


#endif /* VIRTUALOBJECT_H */
