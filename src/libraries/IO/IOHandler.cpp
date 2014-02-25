#include "IOHandler.h"

IOHandler::IOHandler(){
	/* @todo	implement state check and change
	 * 			discuss if implement here or get from Rendermanager -> initialFoV = 45.0f;
	 */
	isMenuState = false;
	camObject = new Camera();
	speed_movement = 3.0f; // 3 units / second
	mouseSpeed = 0.005f;
	deltaTime = 0.1f;	//default value
	currentTime = 0.0;
	xPos = -1;
	yPos = -1;

//	glfwGetCursorPos(window, &xPos, &yPos);
	// Get mouse position
}



// Compute new orientation
void IOHandler::setOrientation(GLFWwindow* window, double xpos, double ypos){
	int Width, Height;
	glfwGetWindowSize(window, &Width, &Height);
	
	if (xPos == -1 && yPos == -1){	//has never been called before
		xPos = Width/2;
		yPos = Height/2;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    else{	// has been called before --> mouse somewhere around middle of window and hidden
	    float gotPhi 	= camObject->getPhi();
	    float gotTheta 	= camObject->getTheta();
	    camObject->setPhi(	gotPhi 		+ mouseSpeed * float(Width / 2 - xpos));			//Horizontal
	    camObject->setTheta(gotTheta 	+ mouseSpeed * float(Height / 2 - ypos));		//Vertikal
	}
	glfwSetCursorPos(window, Width/2, Height/2);
}

void IOHandler::cursorPos_callback(GLFWwindow* window, int xpos, int ypos){
	setOrientation(window, xpos, ypos);

	Subject::notify( "CURSOR_POS_CALLBACK_LISTENER" );
}

void IOHandler::mouseButton_callback(GLFWwindow* window, int button, int action, int mods){
	if (action == GLFW_PRESS){
		notify( button );		//notify button press listener
	}	
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
			camObject->setSpeedForward(speed_movement);
		}

		// Move backward
		if (key == GLFW_KEY_S && action == GLFW_PRESS){
			camObject->setSpeedForward(-speed_movement);
		}

		// Strafe right
		if (key == GLFW_KEY_D && action == GLFW_PRESS){
			camObject->setSpeedRight(speed_movement);
		}

		// Strafe left
		if (key == GLFW_KEY_A && action == GLFW_PRESS){
			camObject->setSpeedRight(-speed_movement);
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

		// Fast movement
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
			float currentSpeedRight = camObject->getSpeedRight();
			float currentSpeedForward = camObject->getSpeedForward();
			camObject->setSpeedRight(  currentSpeedRight*2.0);
			camObject->setSpeedForward(currentSpeedForward*2.0);
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

void IOHandler::attachListenerOnMouseButtonPress(Listener* listener, int button){
	sstream	<<	button;	// convert int to string
	listener->setName( sstream.str()	);
	attach(listener);
	sstream.str("");	// clear stringstream
	sstream.clear();
}

void IOHandler::attachListenerOnCursorPosCallback(Listener* listener){
	listener->setName( "CURSOR_POS_CALLBACK_LISTENER");
	attach(listener);
}