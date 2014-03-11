#ifndef APPLICATION_H
#define APPLICATION_H

#include "Patterns/StateMachine.h"
#include "Patterns/Singleton.h"
#include "Patterns/Subject.h"

#include <string>

/*! @brief Application is a Singleton State Machine (ApplicationContext).
 *
 *	Application is the biggest interface to build your own Executable with our libraries.
 *  Application will initialize a GLFW window by itself and initializes Render Manager and other core functionality.
 *  Application, as a state machine, can switch between states with ease. Application States are supposed to contain everything
 *  which decides what you can see on the window at any given time. I.e. the Render Loop, the Scene itself, Camera settings and Bullet Physics settings.
 *  Especially it's Listener-Interfaces are empowering the user for endless customization
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

	Application(std::string label = "");	//!<Constructor initializes GLFW Window and GLEW for further functionality

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
