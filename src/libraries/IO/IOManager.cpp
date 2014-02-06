	/*
	 * @author Sanèr, Oliver
	 */

#include "IOManager.h"

void IOManager::bindCallbackFuncs(){
	if (window != 0){
		glfwSetKeyCallback(window, staticKey_callback);
		glfwSetCursorPosCallback(window, staticCursorPos_callback);
		glfwSetMouseButtonCallback(window, staticMouseButton_callback);
	}
}

void IOManager::staticKey_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	IOManager::getInstance()->key_callback(window,key,scancode,action,mods);
}	 

void IOManager::staticCursorPos_callback(GLFWwindow* window, double xpos, double ypos){
	IOManager::getInstance()->cursorPos_callback(window, xpos, ypos);
}

void IOManager::staticMouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	IOManager::getInstance()->mouseButton_callback(window, button, action, mods);
}

void IOManager::cursorPos_callback(GLFWwindow* window, double xpos, double ypos){
	// @todo call IOHandler cursorPos func
}

void IOManager::mouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	// @todo call IOHandler mouseButton func
}

IOManager::IOManager(){
	/* @todo	implement state check and change
	 * 			discuss if implement here or get from Rendermanager -> initialFoV = 45.0f;
	 */
	isMenuState = false;
	camObject = new Camera();
	speed_walk = 3.0f; // 3 units / second
	speed_run = 6.0f;
	mouseSpeed = 0.005f;
	window = 0;

	deltaTime = 0.1f; //default deltaTime value: 100ms
	// Get mouse position
}

void IOManager::setWindow(GLFWwindow* window){
	this->window = window;
}

/*
void IOManager::computeFoV(){
	FoV = initialFoV - 5 * glfwGetMouseWheel();
}
*/

void IOManager::setCameraObject(Camera* camera){
		camObject = camera;
	}

Camera* IOManager::getCameraObject(){
		return camObject;
	}

void IOManager::computeFrameTimeDifference(){
	// @todo this doesnt work yet
	// glfwGetTime is called only once, the first time this function is called
	lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	currentTime = glfwGetTime();
	deltaTime = float(currentTime - lastTime);
}

// Compute new orientation
void IOManager::setOrientation(){
	// Reset mouse position for next frame
	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

	float gotPhi = camObject->getPhi();
	float gotTheta = camObject->getTheta();
	camObject->setPhi(gotPhi += mouseSpeed * float(WIDTH / 2 - xPos));
	camObject->setTheta(gotTheta += mouseSpeed * float(HEIGHT / 2 - yPos));
}

void IOManager::computeIO(){
	computeFrameTimeDifference();

	setOrientation();

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
//TODO switch implementations for menu state and game state

void IOManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	if (isMenuState == false){
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
			//not exit but enter menu state
			//glfwSetWindowShouldClose(window, GL_TRUE);
			isMenuState = true;
			return;
		}

		glm::vec3 gotPosition = camObject->getPosition();

		// Move forward
		if (key == GLFW_KEY_W && action == GLFW_REPEAT){
			gotPosition += camObject->getViewDirection() * deltaTime * speed_walk;
			camObject->setPosition(gotPosition);
		}

		// Move backward
		if (key == GLFW_KEY_S && action == GLFW_REPEAT){
			gotPosition -= camObject->getViewDirection() * deltaTime * speed_walk;
			camObject->setPosition(gotPosition);
		}

		// Strafe right
		if (key == GLFW_KEY_D && action == GLFW_REPEAT){
			gotPosition += camObject->getRight() * deltaTime * speed_walk;
			camObject->setPosition(gotPosition);
		}

		// Strafe left
		if (key == GLFW_KEY_A && action == GLFW_REPEAT){
			gotPosition -= camObject->getRight() * deltaTime * speed_walk;
			camObject->setPosition(gotPosition);
		}

		// Fast move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_W) && action == GLFW_REPEAT){
			gotPosition += camObject->getViewDirection() * deltaTime * speed_run;
			camObject->setPosition(gotPosition);
		}

		// Fast move backward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_S) && action == GLFW_REPEAT){
			gotPosition -= camObject->getViewDirection() * deltaTime * speed_run;
			camObject->setPosition(gotPosition);
		}
		// Fast strafe right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_D) && action == GLFW_REPEAT){
			gotPosition += camObject->getRight() * deltaTime * speed_run;
			camObject->setPosition(gotPosition);
		}

		// Fast strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_A) && action == GLFW_REPEAT){
			gotPosition -= camObject->getRight() * deltaTime * speed_run;
			camObject->setPosition(gotPosition);
		}

	}
	else {
		//TODO implement menu keys
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
			//not exit but enter menu state
			//glfwSetWindowShouldClose(window, GL_TRUE);
			isMenuState = false;
			return;
		}

		if (key == GLFW_KEY_F1 && action == GLFW_PRESS){
			//placeholder
		}
	}
}

// keep as reference
/*void IOManager::keyFunction(int key){
	glm::vec3 gotPosition = camObject->getPosition();
	// Move forward
	switch (key){
		case glfwGetKey(window, GLFW_KEY_UP):
			gotPosition += camObject->getViewDirection() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
		// Move backward
		case glfwGetKey(window, GLFW_KEY_DOWN):
			gotPosition -= camObject->getViewDirection() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
		// Strafe right
		case glfwGetKey(window, GLFW_KEY_RIGHT):
			gotPosition += camObject->getRight() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
		// Strafe left
		case glfwGetKey(window, GLFW_KEY_LEFT):
			gotPosition -= camObject->getRight() * deltaTime * speed;
			camObject->setPosition(gotPosition);
			break;
	}
}
*/

//this HAS TO BE put in rendermanager
//glfwSetKeyCallback(window, key_callback);

glm::mat4 IOManager::getViewMatrix(){
	return mViewMatrix;
}
