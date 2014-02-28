#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <sstream>

#include "Camera.h"
#include "Patterns/Subject.h"

/// a class which implements specific input interpretation, i.e. camera movement
class IOHandler : public Subject{
private:

		// TODO implement state check and change
		bool isMenuState; 				/**<Boolean for changing State between Menu und InGame*/
		double speed;
		double xPos, yPos; 	/**<*Mouse Position*/
		float speed_movement; 	 /**<Float for adding to Position*/
		float mouseSpeed; 	 /**<Float for adding to Theta, Phi*/

		glm::mat4 mViewMatrix;	 /**<4*4-Matrix*/

		Camera* camObject;

		std	::	stringstream sstream; /**<* mostly used to convert ints to strings */
public:
	IOHandler();

	void setCameraObject(Camera* camera);
	Camera* getCameraObject();

	/**\brief getter
	 * returns current ViewMatrix
	 */
	glm::mat4 getViewMatrix();

	/**\
	 * @param window where the callback is used
	 * @param the keyboard key that was pressed or released
	 * @param system-specefic scancode of the key
	 * @param use GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	 * @param Bit field describing which modifier keys were held down
	 * @return returns a new Matrix of the camera
	 *
	 */
	void setOrientation(GLFWwindow* window, double xpos, double ypos); // !< method to set the Camera orientation 
	void cursorPos_callback(GLFWwindow* window, int xpos, int ypos);	//!< cursorPos_callback as defined by GLFW
	void mouseButton_callback(GLFWwindow* window, int button, int action, int mods); //!< mouse button callback (press / release) as defined by GLFW
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void notify(int key);	//!< notify Listeners attached to a key pess by using the GLFW integer definitions for keys
	void attachListenerOnKeyPress(Listener* listener, int key); //!< attach a Listener to a key by using the GLFW integer definitions for keys
	void attachListenerOnMouseButtonPress(Listener* listener, int button); //!< attach a Listener to a button press by using the GLFW integer definitions for buttons
	void attachListenerOnCursorPosCallback(Listener* listener);	//!< attach a Listener to the cursor pos callback
};


#endif
