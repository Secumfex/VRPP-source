#ifndef VIRTUALOBJECT_H
#define VIRTUALOBJECT_H
#include "Physics/PhysicsComponent.h"
#include "Visuals/GraphicsComponent.h"

#include <glm/glm.hpp>
#include <vector>

class VirtualObject{
public:

	glm::mat4 modelMatrix;	/**< 4x4Matrix */

	int id;					/**< identification number */

	PhysicsComponent *physicsComponent; 			/**< pointer to the physics component of the VO */
	vector<GraphicsComponent> graphicsComponent;	/**< pointer to the graphics Component of the VO*/

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
	vector<GraphicsComponent*> getGraphicsComponent();

	/** \brief
	*
	* 	@todo detailed description
	*/
	void addGraphicsComponent(GraphicsComponent *graphcomp);
};


#endif /* VIRTUALOBJECT_H */
