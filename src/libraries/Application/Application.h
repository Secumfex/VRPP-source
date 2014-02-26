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
	bool shouldTerminate;
	bool initialized;

public:
	void initialize(); //!< initialize RenderManager and open window
	void terminate();	//!< break program cycle loop

	bool setState(State* state);	//!< calls statechange listener @return true if successful @return false if unsuccessful
	bool setState(std::string state);	//!<returns true if successful, false if unsuccessful, calls statechange listeners

	/*Constructor initializes GLFW Window and GLEW for further functionality*/
	Application(std::string label = "");

	/*! @brief sets the label.
	 *
	 *	@param label is a string representing it's name
	 */
	void setLabel(std::string label);

	std::string getLabel();

	/*Application Listeners*/
	void attachListenerOnStateChange(Listener* listener);           //!< attach a listener that will be called at any successful statechange
	void attachListenerOnBeginningProgramCycle(Listener* listener); //!< attach a listener that will be called at a beginning program cycle (run()-method)
	void attachListenerOnProgramTermination(Listener* listener);    //!< attach a listener that will be called at program termination
	void attachListenerOnProgramInitialization(Listener* listener);    //!< attach a listener that will be called at program initialization
	void attachListenerOnRenderManagerFrameLoop(Listener* listener);	//!< attach a listener to RenderManager through Application, will be called at beginning Frame Rendering Process

	void run(); //!< enter program cycle loop


};

#endif
