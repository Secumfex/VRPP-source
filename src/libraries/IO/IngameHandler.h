#ifndef INGAMEMOVEMENT_H_
#define INGAMEMOVEMENT_H_

#include "IOHandler.h"
#include "Camera.h"

/// IOHandler which comes with default Camera-Movement handling via WASD keys
class IngameHandler : public IOHandler{
private:
		double speed;					/**< auxillary variable  */
		float speed_movement; 			/**< Float for adding to Position */
		float mouseSpeed; 				/**< Float for adding to Theta, Phi */
public:
	/** \brief listener constructor
	 *	
	 */
	IngameHandler();

	/** \brief listener destructor
	 *
	 */
	virtual ~IngameHandler();

	/** \brief listener constructor
	 *
	 * @param window
	 * @param button
	 * @param action
	 * @param mods
	 */
	virtual void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);

	/** \brief custom key callback method which with handles camera control on WASD and shift keys
	 *
	 * @param window
	 * @param key
	 * @param scancode
	 * @param action
	 * @param mods
	 */
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/** \brief custom camera view handling
	 *
	 * @param window
	 * @param xpos,ypos
	 */
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);
};



#endif
