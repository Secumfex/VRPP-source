#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Visuals/Resource.h"

#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"

#include <glm/glm.hpp>
#include <vector>

class RenderQueue;

/// represents a 3D-Model in the scene 
class VirtualObject{

	private:
	glm::mat4 modelMatrix;							/**< 4x4Matrix */

	vector<GraphicsComponent*> mGraphComponent;		/**< vector of graphic-components */

public:
//	vector<GraphicsComponent> graphicsComponent;	/**< pointer to the graphics Component of the VO*/

	/** \brief constructor
	 *
	 * void constructor, sets modelMatrix to zero and creates a new physicsComponent.
	 */
	VirtualObject();

	/** \brief constructor
	 *
	 * if you know a modelMAtrix you can start with this constructor.
	 * it sets modelMatrix to the given one and creates a new physicsComponent.
	 * @param modelMatrix 4x4Matrix
	 */
	VirtualObject(glm::mat4 modelMatrix);

	/** \brief constructor
	 *
	 * creates VirtualObject with min and max vector of the mesh
	 * creates physicComponent with same vectors
	 * @param min,max glm::vec3 vector for max an min x,y and z values
	 * @param mass mass of the rigidBody (physicComponent)
	 * @param collisionFlag sets collisiontype of the collisionshape
	 */
	VirtualObject(glm::vec3 min, glm::vec3 max, float mass = 0.0f, int collisionFlag = 1);

	/** \brief constructor
	 *
	 * creates a sphere as virtual object
	 * creates physicComponent as a sphere as well
	 * @param radius radius of sphere
	 * @param x,y,z position of sphere
	 * @param mass mass of the rigidBody (physicComponent)
	 * @param collisionFlag sets collisiontype of the collisionshape
	 */
	VirtualObject(float radius, float x, float y, float z, float mass = 0.0f, int collisionFlag = 1);

	/** \brief constructor
	 *
	 * creates a box as virtual object
	 * creates physicComponent as a box as well
	 * @param width,height,depth size of the box
	 * @param x,y,z position of box
	 * @param mass mass of the rigidBody (physicComponent)
	 * @param collisionFlag sets collisiontype of the collisionshape
	 */
	VirtualObject(float width, float height, float depth, float x, float y, float z, float mass = 0.0f, int collisionFlag = 1);

	/** \brief destructor
	 *
	 * deletes the physics and graphics components
	 */
	~VirtualObject();

	/** \brief translates the physic and graphic component of the virtual object
	 *
	 * @param trans glm::vec3 translation vector
	 */
	void translate(glm::vec3 trans);

	/** \brief scales the physic and graphic component of the virtual object
	 *
	 * @param scale glm::vec3 scale vector
	 */
	void scale(glm::vec3 scale);

	/** \brief updates the modelMatrix
	 *
	 * fetches the current modelMatrix of the physicsComponent
	 */
	void updateModelMatrixViaPhysics();
	
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

	/** \brief getter
	 *
	 * returns graphic components with a specific/given material name
	 * @param tag graphic component material name
	 * @return vector with graphic components which have the material name of "tag"
	 */
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
	 * creates PhysicComponent of a mesh model
	 * @param mass
	 * @param collisionFlag sets collisiontype of the collisionshape
	 * @return void
	 */
	void setPhysicsComponent(float x, float y, float z, btTriangleMesh btMesh, btTriangleIndexVertexArray* btTIVA);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with box shaped rigid Body
	 * @param min,max smallest and largest x, y, z values of a given model
	 * @param mass
	 * @param collisionFlag sets collisiontype of the collisionshape
	 * @return void
	 */
	void setPhysicsComponent(glm::vec3 min, glm::vec3 max, float mass = 0.0f, int collisionFlag = 1);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with sphere shaped rigid Body
	 * @param radius dimension of the sphere
	 * @param x,y,z origin position in physics world
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @param collisionFlag sets collisiontype of the collisionshape
	 * @return void
	 */
	void setPhysicsComponent(float radius, float x, float y, float z, float mass = 0.0f, int collisionFlag = 1);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with box shaped rigid Body
	 * @param width,height,depth dimension of the box
	 * @param x,y,z origin position in physics world
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @param collisionFlag sets collisiontype of the collisionshape
	 * @return void
	 */
	void setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass = 0.0f, int collisionFlag = 1);

	/** \brief sets PhysicsComponent
	 *
	 * creates PhysicComponent with plane shaped rigid Body
 	 * @param x,y,z origin position in physics world
 	 * @param normal normal vector of the plane
 	 * @param mass defines the behavior of the rigid body in the physics world
 	 * @param collisionFlag sets collisiontype of the collisionshape
 	 * @return void
	 */

	void setPhysicsComponent(float x, float y, float z, glm::vec3 normal, float mass = 0.0f, int collisionFlag = 1);

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

	/** \brief getter
	 *
	 * @return the virtual objects physic component
	 */
	PhysicsComponent* getPhysicsComponent();
};


#endif /* VIRTUALOBJECT_H */
