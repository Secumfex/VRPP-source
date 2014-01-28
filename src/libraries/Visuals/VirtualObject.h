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

	vector<GraphicsComponent*> mGraphComponent;

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
	
	void addGraphicsComponent(GraphicsComponent *graphcomp);

	/** \brief
	*
	* 	@todo detailed description
	*/
	vector<GraphicsComponent*> getGraphicsComponent();

	void setPhysicsComponent();																							//TODO: Dokumentation

	void setPhysicsComponent(glm::mat4 modelMatrix);																	//TODO: Dokumentation

	void setPhysicsComponent(glm::vec3 min, glm::vec3 max);																//TODO: Dokumentation

	void setPhysicsComponent(float radius, float x, float y, float z, float mass);										//TODO: Dokumentation

	void setPhysicsComponent(float width, float height, float depth, float x, float y, float z, float mass);			//TODO: Dokumentation

	glm::mat4 getModelMatrix();

	/** \brief
	*
	* 	@todo detailed description
	*/

	PhysicsComponent *physicsComponent; 			/**< pointer to the physics component of the VO */
};


#endif /* VIRTUALOBJECT_H */
