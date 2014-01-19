#ifndef APPLICATION_H
#define APPLICATION_H

#include "Patterns/StateMachine.h"
#include "Patterns/Singleton.h"
#include "Patterns/Subject.h"

#include <string>

/*! @brief Application is a Singleton State Machine (ApplicationContext).
 *
 *	@todo detailed description pls
 */
class Application : public Singleton<Application>, public StateMachine, public Subject{
friend class Singleton<Application>;

private:
	string label;

public:
	bool setState(State* state);	//!<returns true if successful, false if unsuccessful, calls statechange listeners
	bool setState(std::string state);	//!<returns true if successful, false if unsuccessful, calls statechange listeners

	Application(std::string label = "");

	/*! @brief sets the label.
	 *
	 *	@param label is a string representing blabla detailed description pls
	 */
	void setLabel(std::string label);

	std::string getLabel();

	/*Application Listeners*/
	void attachStateChangeListener(Listener* listener); //!< attach a listener that will be called at any successful statechange
};

#endif
