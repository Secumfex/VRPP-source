#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Camera.h"
#include "Patterns\Singleton.h"

//TODO make singleton
class IOManager : public Singleton<IOManager>{
	friend class Singleton<IOManager>;
//class IOManager{

private:
	/* WINDOW SIZE */
	// TODO get window size from rendermanager
	int WIDTH, HEIGHT;

	/* STATE CHECK */
	// TODO implement state check and change
	bool isMenuState;

	//TODO discuss if implement here or get from Rendermanager
	//float initialFoV;

	// mouse position
	double xPos, yPos;

	float speed_walk;
	float speed_run;
	float mouseSpeed;

	glm::mat4 mViewMatrix;

	static double lastTime;
	double currentTime;
	float deltaTime;

	inline void setOrientation();

	inline void computeFrameTimeDifference();

	Camera* camObject = new Camera();

public:
	//float FoV;
	GLFWwindow* window;
	glm::mat4 getViewMatrix();
	void computeIO();
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//void computeFoV();
};

#endif
