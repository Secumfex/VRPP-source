#ifndef SELECTIONHANDLER_H
#define SELECTIONHANDLER_H

#include "Patterns/Subject.h"
#include "Physics/PhysicsComponent.h"

class PhysicWorld;

class SelectionHandler : public Subject{
protected:
	const btCollisionObject* currentSelection;	/**< currently selected collision shape */
	PhysicWorld* physicWorld;					/**< PhysicWorld */
public:
	/** \brief constructor
	 *
	 * @param pw
	 */
	SelectionHandler(PhysicWorld* pw = 0);

	/** \brief !docu pls!
	 *
	 * true if currentSelection != 0
	 */
	bool somethingIsSelected();

	/** \brief !docu pls!
	 *
	 * attempt ray picking from origin in direction of to
	 * @param from
	 * @param to
	 */
	void trySelection(glm::vec3& from, glm::vec3& to);

	/** \brief handle selection
	 *
	 * !docu pls!
	 */
	virtual void handleSelection();

	/** \brief getter
	 *
	 * get current selection pointer (to where-ever)
	 * @return bullet collision object (currentShape)
	 */
	const btCollisionObject* getCurrentSelection();

	/** \brief attach listener
	 *
	 * attach Listener on Selection Handling
	 * @param listener
	 */
	void attachListenerOnHandleSelection(Listener* listener);

	/** \brief attach listener
	 *
	 * attach Listener on Selection attempt
	 * @param listener
	 */
	void attachListenerOnTrySelection(Listener* listener);	
};

#endif
