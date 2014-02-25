#include "IOHandler.h"
#include <math.h>

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
void IOHandler::setOrientation(GLFWwindow* window, double xpos, double ypos){
	// Reset mouse position for next frame						CHECK
	//////TODO ERSETZE ZAHLEN DURCH WINDOW KOORDINATEN!!!!!		CHECK
	double xpos1, ypos1;
	glfwGetCursorPos(window, &xpos, &ypos);
	int Width, Height;
    glfwSetWindowSize(window, Width, Height);
	glfwSetCursorPos(window, Width/2, Height/2);
    float gotPhi = camObject->getPhi();
    float gotTheta = camObject->getTheta();
    camObject->setPhi(gotPhi += mouseSpeed * float(Width / 2 - xpos));			//Horizontal
    camObject->setTheta(gotTheta += mouseSpeed * float(Height / 2 - ypos));		//Vertikal
}

void IOHandler::cursorPos_callback(GLFWwindow* window, int xpos, int ypos){
	glm::vec3 direction(cos(camObject->getTheta()) * sin(camObject->getPhi()),sin(camObject->getTheta()),cos(camObject->getTheta()) * cos(camObject->getPhi()));
	//Schauvektor :-)


};

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
		}

		if (key == GLFW_KEY_F1 && action == GLFW_PRESS){
			//placeholder
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
