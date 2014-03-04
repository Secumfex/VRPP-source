#ifndef MENUHANDLER_H_
#define MENUHANDLER_H_

#include "IOHandler.h"
#include "Camera.h"


class MenuHandler : public IOHandler{
private:
public:
	MenuHandler();
	virtual ~MenuHandler();
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);
};



#endif
