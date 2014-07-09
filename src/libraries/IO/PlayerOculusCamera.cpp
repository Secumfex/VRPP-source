#include "PlayerOculusCamera.h"

#define PI 3.14159265f

PlayerOculusCamera::PlayerOculusCamera(Oculus* oculus)
{
	this->oculus = oculus;
	xPosition = 0.0;
	yPosition = 0.0;
	zPosition = 5.0;

	// Initial position : on +Z
	position = glm::vec3(xPosition, yPosition, zPosition);

	// Initial horizontal angle : toward -Z
	phi = PI;
	// Initial vertical angle : none
	theta = 0.0f;

	speedRight = 0.0f;
	speedForward = 0.0f;

	//compute initial View Direction vector
	updateViewDirection();

	/* additional PlayerCameraFunctionality */
	collisionShape = 0;
	rigidBody = 0;

	createCollisionShape();
	createRigidBody();
}


PlayerOculusCamera::~PlayerOculusCamera(void)
{
	delete collisionShape;
	delete rigidBody;
}
void PlayerOculusCamera::createCollisionShape(){
	this->collisionShape = new btCylinderShape(btVector3(0.25,0.5,0.25));	// create a Collision Shape with height = 1, radius = 0.5
}

void PlayerOculusCamera::createRigidBody(){
	if (collisionShape != 0){
		//set Position of rigid body associated with this Player Camera
		btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(xPosition,yPosition,zPosition))); 
		// mass  =  1.0, intertia tensor : no rotation wanted
		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(1.0,motionState,collisionShape,btVector3(0,0,0)); 
	    rigidBody = new btRigidBody(rigidBodyCI);	// create a rigid body from the information provided
    	rigidBody->setActivationState(DISABLE_DEACTIVATION);	// so disable getting "stuck" after some time
    }
}

void PlayerOculusCamera::updatePosition(float deltaTime){
	//overwrite current Position with current Rigid Body Position and Apply current Movementforces
	if (rigidBody != 0){
		// @todo setLinearVelocity as proposed by movement speeds
		btVector3 old_linearVelocity = rigidBody->getLinearVelocity();
		
		glm::vec3 linVelocity 	= 	(getViewDirection()); // view direction minus y component
		linVelocity.y = 0.0f;	// set y to 0
		linVelocity = glm::normalize(linVelocity) 	* speedForward; //normalize and multiply
		linVelocity += 	 	getRight() 				* speedRight; // multiply with current speed
		

		rigidBody->setLinearVelocity(btVector3(linVelocity.x,old_linearVelocity.getY(),linVelocity.z));
		
		// read current position of rigid Body and overwrite Camera-Position
	    btVector3 rigidBody_pos = rigidBody->getWorldTransform().getOrigin();
	    Camera::setPosition(glm::vec3(rigidBody_pos.getX(), rigidBody_pos.getY() + 0.25f, rigidBody_pos.getZ()));
	}	
}

void PlayerOculusCamera::setPosition(glm::vec3 newPos){
	if (rigidBody != 0){
		btVector3 new_position(newPos.x,newPos.y,newPos.z); 
		btTransform transform = rigidBody -> getCenterOfMassTransform();
		transform.setOrigin(new_position);
		rigidBody -> setCenterOfMassTransform(transform);
		newPos.y += 0.25f;
		Camera::setPosition(newPos);	// set the other old stuff for consistency
	}
}

void PlayerOculusCamera::setPosition(float x, float y, float z){
	setPosition(glm::vec3(x,y,z));
}

btRigidBody* PlayerOculusCamera::getRigidBody(){
	return rigidBody;
}

btCollisionShape* PlayerOculusCamera::getCollisionShape(){
	return collisionShape;
}