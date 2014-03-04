#ifndef INGAMEMOVEMENT_H_
#define INGAMEMOVEMENT_H_

#include "IOHandler.h"
#include "Camera.h"


class IngameHandler : public IOHandler{
private:
public:
	IngameHandler();
	virtual ~IngameHandler();
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void setOrientation(GLFWwindow* window, double xpos, double ypos);
};



#endif
