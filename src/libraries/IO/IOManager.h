#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include "Patterns\Singleton.h"
#include "Camera.h"


class IOManager : public Singleton<IOManager>{
	friend class Singleton<IOManager>;

private:
	// TODO get window size from rendermanager
	int WIDTH, HEIGHT; /**<Size for window*/

	// TODO implement state check and change
	bool isMenuState; /**<Boolean for changing State between Menu und InGame*/

	//TODO discuss if implement here or get from Rendermanager
	//float initialFoV;

	double xPos, yPos; 	/**<*Mouse Position*/
	float speed_walk; 	 /**<Float for adding to Position*/
	float speed_run;  	 /**<Float for adding to Position*/
	float mouseSpeed; 	 /**<Float for adding to Theta, Phi*/

	glm::mat4 mViewMatrix;	 /**<4*4-Matrix*/

	double lastTime;		/**<Double for lastTime*/
	double currentTime;			/**<Double for currentTime*/
	float deltaTime;			/**<Float for time bewteen lastTime and CurrentTime*/

	inline void setOrientation();
	inline void computeFrameTimeDifference();

	Camera* camObject;

	IOManager();
public:
	void setWindow(GLFWwindow* window);

	void setCameraObject(Camera* camera);	/**< set camera pointer */
	Camera* getCameraObject();				/**< get camera pointer */

	//float FoV;
	GLFWwindow* window;

	/**\brief getter
	 * returns current ViewMatrix
	 */
	glm::mat4 getViewMatrix();

	/**\brief Update
		 * Get a DeltaTime and set an orientation for camera witch mouse
		 */
	void computeIO();

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
	//void computeFoV();
	
	void cursorPos_callback(GLFWwindow* window, double xpos, double ypos);	//!< cursor position callback (movement)
	void mouseButton_callback(GLFWwindow* window, int button, int action, int mods); //!< mouse button callback (press / release)


	/**
	 * @brief method to register at glfwKeyCallback
	 * @details GLFW needs to use a static method which cannot be provided by instance methods
	 */
	static void staticKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods); //!< static method to be registered at GLFW
	static void staticCursorPos_callback(GLFWwindow* window, double xpos, double ypos);	//!< static method to be registered at GLFW
	static void staticMouseButton_callback(GLFWwindow* window, int button, int action, int mods); //!< static method to be registerted at GLFW

	/// register callback method by binding the static callback methods
	void bindCallbackFuncs();
};

#endif
