#ifndef INGAMEMOVEMENT_H_
#define INGAMEMOVEMENT_H_

#include "IOHandler.h"
#include "Camera.h"


class IngameHandler : public IOHandler{
private:
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
	 * @param xpos,xpos
	 */
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);
};



#endif
