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
	string label;			/**< label of this Application, displayed in Window Header */
	bool shouldTerminate;	/**< auxillary bool to determine whether the application should terminate */
	bool initialized;		/**< auxillary bool to determine whether the application has been initialized yet */

public:
	/** \brief initialize RenderManager and open window
	 *
	 */
	void initialize();

	/** \brief break program cycle loop
	 *
	 */
	void terminate();

	/** \brief calls statechange listener
	 *
	 * @param state state as State reference
	 * @return true if successful
	 * @return false if unsuccessful
	 */
	bool setState(State* state);

	/** \brief calls statechange listeners
	 *
	 * @param state state as string
	 * @return true if successful
	 * @return false if unsuccessful
	 */
	bool setState(std::string state);

	/** \brief Constructor initializes GLFW Window and GLEW for further functionality
	 *
	 */
	Application(std::string label = "");

	/*! @brief sets the label.
	 *
	 *	@param label is a string representing it's name
	 */
	void setLabel(std::string label);

	/** \brief getter
	 *
	 * @return label (string)
	 */
	std::string getLabel();

	/*Application Listeners*/
	/** \brief attach listener
	 *
	 * attach a listener that will be called at any successful statechange
	 * @param listener
	 */
	void attachListenerOnStateChange(Listener* listener);

	/** \brief attach listener
	 *
	 * attach a listener that will be called at a beginning program cycle (run()-method)
	 * @param listener
	 */
	void attachListenerOnBeginningProgramCycle(Listener* listener);

	/** \brief attach listener
	 *
	 * attach a listener that will be called at program termination
	 * @param listener
	 */
	void attachListenerOnProgramTermination(Listener* listener);

	/** \brief attach listener
	 *
	 * attach a listener that will be called at program initialization
	 * @param listener
	 */
	void attachListenerOnProgramInitialization(Listener* listener);

	/** \brief attach listener
	 *
	 * attach a listener to RenderManager through Application, will be called at beginning Frame Rendering Process
	 * @param listener
	 */
	void attachListenerOnRenderManagerFrameLoop(Listener* listener);

	/** \brief enter program cycle loop
	 *
	 */
	void run();

};

#endif
