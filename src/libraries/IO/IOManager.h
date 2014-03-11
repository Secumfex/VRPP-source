#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <sstream>
#include "Patterns\Singleton.h"
#include "IO\IOHandler.h"
#include "Patterns/Subject.h"

/// singleton implementation of a class to handle input callbacks and call specific callback methods of it's current IOHandler
class IOManager : public Singleton<IOManager>, Subject{
	friend class Singleton<IOManager>;

private:
	int WIDTH, HEIGHT; /**<Size for window, is set when window pointer is set, else 0*/
	double xPos, yPos; 	/**<*Mouse Position*/

	double lastTime;		/**<Double for lastTime*/
	double currentTime;			/**<Double for currentTime*/
	float deltaTime;			/**<Float for time bewteen lastTime and CurrentTime*/

	IOHandler* currentIOHandler; /**<* active IOHandler Object */

	std	::	stringstream sstream; /**<* mostly used to convert ints to strings */

	IOManager();
public:
	void setWindow(GLFWwindow* window);

	GLFWwindow* window;

	void setCurrentIOHandler(IOHandler* iOHandler);
	IOHandler* getCurrentIOHandler();

	float getDeltaTime();	//!< get time difference with which IOManager is working	
	float* getDeltaTimePointer(); //!< get pointer to delta time variable, use with caution!
	float getLastTime ();	//!< get last time on which computeFrameTimeDifference was called 

	void computeFrameTimeDifference();	//!< compute time difference since last call of this method

	/**\
	 * @param window where the callback is used
	 * @param the keyboard key that was pressed or released
	 * @param system-specefic scancode of the key
	 * @param use GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	 * @param Bit field describing which modifier keys were held down
	 * @return returns a new Matrix of the camera
	 *
	 */
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	void cursorPos_callback(GLFWwindow* window, double xpos, double ypos);	//!< cursor position callback (movement)
	void mouseButton_callback(GLFWwindow* window, int button, int action, int mods); //!< mouse button callback (press / release)


	/**
	 * @brief method to register at glfwKeyCallback
	 * @details GLFW needs to use a static method which cannot be provided by instance methods
	 */
	static void staticKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods); //!< static method to be registered at GLFW
	static void staticCursorPos_callback(GLFWwindow* window, double xpos, double ypos);	//!< static method to be registered at GLFW
	static void staticMouseButton_callback(GLFWwindow* window, int button, int action, int mods); //!< static method to be registerted at GLFW

	/// register callback methods by binding the static callback methods
	void bindCallbackFuncs();


	void notify(int key);	//!< notify Listeners attached to a key pess by using the GLFW integer definitions for keys
	void attachListenerOnKeyPress(Listener* listener, int key);//!< attach a Listener to a key by using the GLFW integer definitions for keys
};

#endif
