#ifndef MENUHANDLER_H_
#define MENUHANDLER_H_

#include "IOHandler.h"
#include "Camera.h"

/// IOHandler which comes with Mouse selection and a visible mouse
class MenuHandler : public IOHandler{
private:
public:
	/** \brief constructor
	 *
	 */
	MenuHandler();

	/** \brief destructor
	 *
	 */
	virtual ~MenuHandler();

	/** \brief key callback function without any predefined handling
	 *
	 * @param window
	 * @param key
	 * @param scancode
	 * @param action
	 * @param mods
	 */
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/** \brief auxillary function to set mouse visibility and behaviour
	 *
	 * @param window
	 * @param xpos,ypos
	 */
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);
};



#endif
