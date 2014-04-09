#ifndef IOHANDLER_H_
#define IOHANDLER_H_




#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <sstream>


#include "Patterns/Subject.h"
#include "SelectionHandler.h"
#include "Camera.h"





/// a class which implements specific input interpretation, i.e. camera movement
class IOHandler : public Subject{
protected:
		// TODO implement state check and change
		bool isMenuState; 				/**< Boolean for changing State between Menu und InGame */
		double xPos, yPos; 				/**< Mouse Position */

		glm::mat4 mViewMatrix;			/**< 4*4-Matrix */

		Camera* camObject;				/**< camera object which may be manipulated through input callbacks */

		std	::	stringstream sstream; 	/**<* mostly used to convert ints to strings */	

		SelectionHandler* selectionHandler;	/**< Mouse selection handler class which uses Bullet Ray Casting */
public:

	/** \brief constructor
	 *
	 */
	IOHandler();

	/** \brief destructor
	 *
	 */
	virtual ~IOHandler();

	/** \brief setter
	 *
	 * sets/changes camObject
	 * @param camera
	 */
	void setCameraObject(Camera* camera);

	/** \brief getter
	 *
	 * @return camObject
	 */
	Camera* getCameraObject();

	/** \brief setter
	 *
	 * sets/changes selectionHandler
	 * @param selectionHandler
	 */
	void setSelectionHandler(SelectionHandler* selectionHandler);

	/** \brief getter
	 *
	 * @return selectionHandler
	 */
	SelectionHandler* getSelectionHandler();

	/**\brief getter
	 * returns current ViewMatrix
	 */
	glm::mat4 getViewMatrix();

	/** \brief setter
	 *
	 * method to set the Camera orientation
	 * @param window
	 * @param xpos,ypos
	 */
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);

	/** \brief custom mouse position handling function
	 *
	 * cursorPos_callback as defined by GLFW
	 * @param window
	 * @param xpos,ypos
	 */
	virtual void cursorPos_callback(GLFWwindow* window, int xpos, int ypos);

	/** \brief custom mouse button handling function
	 *
	 * mouse button callback (press / release) as defined by GLFW
	 * @param window
	 * @param button
	 * @param action
	 * @param mods
	 */
	virtual void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);

	/** \brief custom key callback interpretation
	 *
	 * @param window window where the callback is used
	 * @param key the keyboard key that was pressed or released
	 * @param scancode system-specefic scancode of the key
	 * @param action use GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	 * @param mods Bit field describing which modifier keys were held down
	 * @return returns a new Matrix of the camera
	 */
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/** \brief notify listeners attached to a certain GLFW key
	 *
	 * notify Listeners attached to a key pess by using the GLFW integer definitions for keys
	 * @param key
	 */
	void notify(int key);

	/** \brief attach listener
	 *
	 * attach a Listener to a key by using the GLFW integer definitions for keys
	 * @param listener
	 * @param key
	 */
	void attachListenerOnKeyPress(Listener* listener, int key);

	/** \brief attach listener
	 *
	 * attach a Listener to a button press by using the GLFW integer definitions for buttons
	 * @param listener
	 * @param button
	 */
	void attachListenerOnMouseButtonPress(Listener* listener, int button);

	/** \brief attach listener
	 *
	 * attach a Listener to the cursor pos callback
	 * @param listener
	 */
	void attachListenerOnCursorPosCallback(Listener* listener);
};


#endif
