#ifndef IOHANDLER_H_
#define IOHANDLER_H_

#include "Camera.h"
#include "IOManager.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class IOHandler{
private:

		// TODO implement state check and change
		bool isMenuState; 				/**<Boolean for changing State between Menu und InGame*/

		double xPos, yPos; 	/**<*Mouse Position*/
		float speed_walk; 	 /**<Float for adding to Position*/
		float speed_run;  	 /**<Float for adding to Position*/
		float mouseSpeed; 	 /**<Float for adding to Theta, Phi*/

		glm::mat4 mViewMatrix;	 /**<4*4-Matrix*/

		static double lastTime;		/**<Double for lastTime*/
		double currentTime;			/**<Double for currentTime*/
		float deltaTime;			/**<Float for time bewteen lastTime and CurrentTime*/

		inline void setOrientation();
		inline void computeFrameTimeDifference();

		Camera* camObject;
public:
	/**\brief getter
	 * returns current ViewMatrix
	 */
	glm::mat4 getViewMatrix();
	/**\
	 * Get a DeltaTime and set an orientation for camera witch mouse
	 */
	void ComputeIO();
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
};


#endif
