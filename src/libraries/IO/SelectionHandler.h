#ifndef SELECTIONHANDLER_H
#define SELECTIONHANDLER_H

#include "Patterns/Subject.h"
#include "Physics/PhysicsComponent.h"

class PhysicWorld;

class SelectionHandler : public Subject{
protected:
	void* currentSelection;
	PhysicWorld* physicWorld;
public:
	SelectionHandler(PhysicWorld* pw = 0);
	bool somethingIsSelected();		//!< true if currentSelection != 0

	void trySelection(glm::vec3& from, glm::vec3& to);	//!< attempt ray picking from origin in direction of to
	virtual void handleSelection();	//!< handle selection

	void* getCurrentSelection();	//!< get current selection pointer (to where-ever) 

	void attachListenerOnHandleSelection(Listener* listener);	//!< attach Listener on Selection Handling 
	void attachListenerOnTrySelection(Listener* listener); 	//!< attach Listener on Selection attempt
};

#endif