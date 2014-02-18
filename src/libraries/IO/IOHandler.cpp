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

void IOHandler::setCameraObject(Camera* camera){
	camObject = camera;
}

Camera* IOHandler::getCameraObject(){
	return camObject;
}