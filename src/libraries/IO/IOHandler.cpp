#include "IOHandler.h"

IOHandler::IOHandler(){
	/* @todo	implement state check and change
	 * 			discuss if implement here or get from Rendermanager -> initialFoV = 45.0f;
	 */
	isMenuState = false;
	camObject = new Camera();
	speed_walk = 3.0f; // 3 units / second
	speed_run = 6.0f;
	mouseSpeed = 0.005f;
	deltaTime = 0.1f;	//default value
	currentTime = 0.0;
	xPos = 0;
	yPos = 0;
//	glfwGetCursorPos(window, &xPos, &yPos);
	// Get mouse position
}

// Compute new orientation
void IOHandler::setOrientation(){
	// Reset mouse position for next frame
	//////TODO ERSETZE ZAHLEN DURCH WINDOW KOORDINATEN!!!!!
//	glfwSetCursorPos(window, 100, 100);

	float gotPhi = camObject->getPhi();
	float gotTheta = camObject->getTheta();
	camObject->setPhi(gotPhi += mouseSpeed * float(100 / 2 - xPos));
	camObject->setTheta(gotTheta += mouseSpeed * float(100 / 2 - yPos));
}

void IOHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (isMenuState == false){
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
			//not exit but enter menu state
			//glfwSetWindowShouldClose(window, GL_TRUE);
			isMenuState = true;
		}

		glm::vec3 gotPosition = camObject->getPosition();

		// Move forward
		if (key == GLFW_KEY_W && action == GLFW_PRESS){
			camObject->setSpeedForward(speed_walk);
		}

		// Move backward
		if (key == GLFW_KEY_S && action == GLFW_PRESS){
			camObject->setSpeedForward(-speed_walk);
		}

		// Strafe right
		if (key == GLFW_KEY_D && action == GLFW_PRESS){
			camObject->setSpeedRight(speed_walk);
		}

		// Strafe left
		if (key == GLFW_KEY_A && action == GLFW_PRESS){
			camObject->setSpeedRight(-speed_walk);
		}

		if (key == GLFW_KEY_W && action == GLFW_RELEASE){
			camObject->setSpeedForward(0.0);
		}

		if (key == GLFW_KEY_S && action == GLFW_RELEASE){
			camObject->setSpeedForward(0.0);
		}

		if (key == GLFW_KEY_D && action == GLFW_RELEASE){
			camObject->setSpeedRight(0.0);
		}

		if (key == GLFW_KEY_A && action == GLFW_RELEASE){
			camObject->setSpeedRight(0.0);
		}

		// Fast move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_W) && action == GLFW_PRESS){
			camObject->setSpeedForward(speed_run);
		}

		// Fast move backward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_S) && action == GLFW_PRESS){
			camObject->setSpeedForward(-speed_run);
		}

		// Fast strafe right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_A) && action == GLFW_PRESS){
			camObject->setSpeedRight(speed_run);
		}

		// Fast strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_D) && action == GLFW_PRESS){
			camObject->setSpeedRight(-speed_run);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_W) && action == GLFW_RELEASE){
			camObject->setSpeedForward(0.0);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_S) && action == GLFW_RELEASE){
			camObject->setSpeedForward(0.0);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_A) && action == GLFW_RELEASE){
			camObject->setSpeedRight(0.0);
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT && GLFW_KEY_D) && action == GLFW_RELEASE){
			camObject->setSpeedRight(0.0);
		}


	}
	if (action != GLFW_RELEASE){	// 	so listeners are only called on pess event, not on release ( i.e. twice )
		notify(key);				//	notify listeners
	}
}

void IOHandler::setCameraObject(Camera* camera){
	camObject = camera;
}

Camera* IOHandler::getCameraObject(){
	return camObject;
}

void IOHandler::attachListenerOnKeyPress(Listener* listener, int key){
	sstream	<<	key;	// convert int to string
	listener->setName( sstream.str()	);
	attach(listener);
	sstream.str("");	// clear stringstream
	sstream.clear();
}

void IOHandler::notify(int key){
	sstream << key;		// convert int to string
	Subject :: notify( sstream.str() );
	sstream.str("");	// clear stringstream
	sstream.clear();
}
