#ifndef APPLICATIONLISTENERS_H
#define APPLICATIONLISTENERS_H

/// This header contains various Application class related Listeners

#include "Patterns/Listener.h"
class Application;

/// base class for application listeners, has no functionality
class ApplicationListener : public Listener {
protected:	
	Application* application;	/**< !docu pls! */
public:
	/** \brief listener constructor
	 *
	 * @param application
	 */
	ApplicationListener(Application* application = 0);

	/** \brief update
	 *
	 */
	virtual void update();	
};

/// Activates the Application's current state
class ActivateStateListener : public ApplicationListener{
private:
	Application* application;	/**< !docu pls! */
public:
	/** \brief listener constructor
	 *
	 * @param application
	 */
	ActivateStateListener(Application* application);

	/** \brief update
	 *
	 */
	void update();
};

/// sets the Application State to whatever (think about buttons)
class SetStateListener : public ApplicationListener{
private:
	std::string state;	/**< !docu pls! */
public:
	/** \brief listener constructor
	 *
	 * @param application
	 * @param state
	 */
	SetStateListener(Application* application, std::string state);

	/** \brief update
	 *
	 */
	void update();
};

/// terminates the Application (breaks the program cycle loop)
class TerminateApplicationListener : public ApplicationListener{
private:
	Application* application;	/**< !docu pls! */
public:
	/** \brief listener constructor
	 *
	 * @param application
	 */
	TerminateApplicationListener(Application* application);

	/** \brief update
	 *
	 */
	void update();
};

#endif
