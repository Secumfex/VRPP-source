#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <glm/glm.hpp>
#include "btBulletDynamicsCommon.h"


using namespace std;

class VirtualObject;

/*! @brief PhysicsComponent.
 *
 *	the physic component is one part of a virtual object. it contains all needed parts for the bullet physics simulation.
 */
class PhysicsComponent{
private:

	btRigidBody *rigidBody;	/**< bullet rigid body */

	bool hit;				/**< true if hit by an other object, else false */

public:

	/** \brief constructor
	*
	* Default constructor with no values.
	*/
	PhysicsComponent();

	/** \brief constructor
	*
	* creates a physics component with a given model matrix. does not define any rigid body.
	* @param modelMatrix 4x4Matrix
	*/
	PhysicsComponent(glm::mat4 modelMatrix);

	/** \brief constructor
	*
	* constructor to create a box shaped rigid body.
	* @param min,max contain smallest and largest x, y, z values of a given model (in VirtualObjectFactory class)
	* @param mass defines the behavior of the rigid body in the physics world
	* @param collisionFlag number of wanted flag, for possible flags see method "addCollitionFlag"
	*/
	PhysicsComponent(glm::vec3 min, glm::vec3 max, float mass, int collisionFlag);

	/** \brief constructor
	*
	* constructor to create a sphere shaped rigid body.
	* @param radius dimension of the sphere
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	* @param collisionFlag number of wanted flag, for possible flags see method "addCollitionFlag"
	*/
	PhysicsComponent(float radius, float x, float y, float z, float mass, int collisionFlag);

	/** \brief constructor
	*
	* constructor to create a box shaped rigid body.
	* @param width,height,depth  dimensions of the box
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	* @param collisionFlag number of wanted flag, for possible flags see method "addCollitionFlag"
	*/
	PhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass, int collisionFlag);

	/** \brief constructor
	 *
	 * constructor to create a static plane shaped rigid body.
	 * @param x,y,z start position in the world
	 * @param normal normal vector of the plane
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @param collisionFlag number of wanted flag, for possible flags see method "addCollitionFlag"
	 */
	PhysicsComponent(float x, float y, float z, glm::vec3 normal, float mass, int collisionFlag);

	/** \brief constructor
	 *
	 * constructor to create a heightfieldterrainshaped rigid body (btHeightfieldTerrainShape).
	 * @param filename filename of the heightfield picture
	 * @param x,y,z
	 */
	PhysicsComponent(char* filename, float x, float y, float z);

	/** \brief destructor
	*
	* clears the allocated memory. deletes shape, motionState and rigidBody.
	*/
	~PhysicsComponent();

	/** \brief translates a rigidBody to another position
	 *
	 * @param pos new position
	 */
	void translate(glm::vec3 pos);

	/** \brief translates a rigidBody to another position
	 *
	 * @param scale vec3 which contains x,y,z values for scaling
	 * @param vo virtual object reference
	 */
	void scale(glm::vec3 scale, VirtualObject* vo);

	/** \brief changes the collision flag of the rigid body
	*
	* ORed current flag with the wanted one.
	* possible flags are:
	*  CF_STATIC_OBJECT = 1, ->no gravity
	*  CF_KINEMATIC_OBJECT = 2,
  	*  CF_NO_CONTACT_RESPONSE = 4, ->no interaction/collision with other objects
  	*  CF_CUSTOM_MATERIAL_CALLBACK = 8,
  	*  CF_CHARACTER_OBJECT = 16,
  	*  CF_DISABLE_VISUALIZE_OBJECT = 32,
  	*  CF_DISABLE_SPU_COLLISION_PROCESSING = 64
	* @param flag number of the wanted flag, 1 for ..., 4 for CF_CUSTOM_MATERIAL_CALLBACK, ...
	* @return void
	*/
	void addCollisionFlag(int flag);

	/** \brief changes the collision flag of the rigid body
	*
	* deletes current flag and sets the wanted one.
	* possible flags are:
	*  CF_STATIC_OBJECT = 1, ->no gravity
	*  CF_KINEMATIC_OBJECT = 2,
  	*  CF_NO_CONTACT_RESPONSE = 4, ->no interaction/collision with other objects
  	*  CF_CUSTOM_MATERIAL_CALLBACK = 8,
  	*  CF_CHARACTER_OBJECT = 16,
  	*  CF_DISABLE_VISUALIZE_OBJECT = 32,
  	*  CF_DISABLE_SPU_COLLISION_PROCESSING = 64
	* @param flag number of the wanted flag, 1 for ..., 4 for CF_CUSTOM_MATERIAL_CALLBACK, ...
	* @return void
	*/
	void setCollisionFlag(int flag);

	/** \brief defines the rigid body as a box
	*
	* creates a box shaped rigid body with all necessary parts.
	* @param width,height,depth  dimensions of the box
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	* @return bullet rigid body
	*/
	btRigidBody* addBox(float width, float height, float depth, float x, float y, float z, float mass);

	/** \brief defines the rigid body as a sphere
	*
	* creates a sphere shaped rigid body with all necessary parts.
	* @param radius dimension of the sphere
	* @param x,y,z start position in the world
	* @param mass defines the behavior of the rigid body in the physics world
	* @return a bullet rigid body
	*/
	btRigidBody* addSphere(float radius, float x, float y, float z, float mass);

	/** \brief defines the rigid body as plane
	 *
	 * creates a plane shaped rigid body with all necessary parts.
	 * @param x,y,z start position in the world
	 * @param normal normal vector of the plane
	 * @param mass defines the behavior of the rigid body in the physics world
	 * @return a bullet rigid body
	 */

	btRigidBody* addPlane(float x, float y, float z, glm::vec3 normal, float mass);

	/** \brief defines the rigid body as heightfield
	 *
	 * creates a heightfield rigid body with all necessary parts
	 * @param filename name of the heightfield picture
	 * @param x,y,z start position in the world
	 * @return a bullet rigid body
	 */
	btRigidBody* addHeightfield(char* filename, float x, float y, float z);


	/** \brief getter
	 *
	 * @return current modelMatrix
	 */
	glm::mat4 getModelMatrix();

	/** \brief getter
	 *
	 * @return current rigidBody
	 */
	btRigidBody* getRigidBody();

	/** \brief setter
	*
	* sets/changes the position of a PhysicsComponent
	* @param x,y,z new position in physics world
	*/
	void setPosition(float x, float y, float z);

	/** \brief getter
	*
	* @return a glm vec 3, the position of the PhysicsComponent
	*/
	glm::vec3 getPosition();


	/** \brief getter
	 *
	 * @return current hit state
	 */
	bool getHit();

	/** \brief setter
	 *
	 * sets current hit state
	 * @param hit true if hit, false if not
	 */
	void setHit(bool hit);


	/** \brief updates the model matrix
	*
	* updates the modelMatrix by the rigid body's behavior in the physics world.
	* @param vo VirtualObject pointer
	*/
	void update(VirtualObject* vo);
};

#endif
