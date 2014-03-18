#ifndef SELECTIONHANDLER_H
#define SELECTIONHANDLER_H

#include "Patterns/Subject.h"
#include "Physics/PhysicsComponent.h"

class PhysicWorld;

/// class to handle object selection via bullet ray casting
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

	/** \brief check whether anything is currently selected
	 *
	 * true if currentSelection != 0
	 */
	bool somethingIsSelected();

	/** \brief perform a selection attempt from one point to another 
	 *
	 * attempt ray picking from one point to another
	 * @param from : origin of ray
	 * @param to : end of ray
	 */
	void trySelection(glm::vec3& from, glm::vec3& to);

	/** \brief handle selection
	 *
	 * perform custom action on selection. simply calls listeners by default
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
