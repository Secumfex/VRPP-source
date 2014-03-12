#ifndef MENUHANDLER_H_
#define MENUHANDLER_H_

#include "IOHandler.h"
#include "Camera.h"


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

	/** \brief !docu pls!
	 *
	 * @param window
	 * @param key
	 * @param scancode
	 * @param action
	 * @param mods
	 */
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/** \brief !docu pls!
	 *
	 * @param window
	 * @param xpos,ypos
	 */
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);
};



#endif
