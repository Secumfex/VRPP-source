#ifndef LISTENERS_H
#define LISTENERS_H

/// This Header contains various general purpose Listeners

#include <Patterns/Listener.h>
#include <string.h>
#include <time.h>
#include <glm/glm.hpp>


/// Listener which prints a predefined message on the console when notified
class PrintMessageListener : public Listener{
private: 
	std::string message;	/**< message as string */
public:
	/** \brief Constructor
	 *
	 * @param message string to be printed to the console upon update
	 */
	PrintMessageListener(std::string message);

	/** \brief update
	 *
	 * prints the message to console
	 */
	void update();

	/** \brief getter
	 *
	 * @return current message
	 */
	std::string getMessage();

	/** \brief setter
	 *
	 * sets/changes message
	 * @param message
	 */
	void setMessage(std::string message);
};

class StateMachine;
/// Listener which prints the name of the current state of the state machine
class PrintCurrentStateListener : public Listener{
private:
	StateMachine* stateMachine;		/**< !docu pls! */
public:
	/** \brief Constructor
	 *
	 * @param stateMachine state machine of interest
	 */
	PrintCurrentStateListener(StateMachine* stateMachine);

	/** \brief update
	 *
	 * prints the name of current state machine to console
	 */
	void update();
};

/// Listener which will call another listener when called after a set amount of time
class TimedTriggerListener : public Listener{
private:
	Listener* target;			/**< !docu pls! */
	float milliseconds; 		/**< set time before target may be called */
	float current_time; 		/**< time since first call */
	bool running;				/**< true after the first update() call */
	bool listener_triggered;	/**< true after time is greater than  */
	clock_t last_clock_call;	/**< !docu pls! */
public:
	/** \brief Constructor
	 *
	 * @param target pointer to the Listener supposed to be callable after a set amount of time
	 * @param milliseconds time before target listener becomes will be called upon the next update
	 */
	TimedTriggerListener(Listener* target, float milliseconds);

	/** \brief update
	 *
	 * triggers next listener
	 */
	void update();
};

/// Listener which prints the value pointed and print that other stuff in front of it
class PrintValueListener : public Listener{
private:
	float* value;			/**< !docu pls! */
	std::string message;	/**< message as string */
public:

	/** \brief Constructor
	 *
	 * @param value pointer to the float variable of interest
	 * @param message string to be printed in front of it
	 */
	PrintValueListener(float* value, std::string message = "");

	/** \brief update
	 *
	 * prints the value to console
	 */
	void update();
};

/// Listener which prints the vector pointed and print that other stuff in front of it
class PrintVec3Listener : public Listener{
private:
	glm::vec3* vector;			/**< !docu pls! */
	std::string message;	/**< message as string */
public:

	/** \brief Constructor
	 *
	 * @param vector pointer to the vector variable of interest
	 * @param message string to be printed in front of it
	 */
	PrintVec3Listener(glm::vec3* vector, std::string message = "");

	/** \brief update
	 *
	 * prints the vector to console
	 */
	void update();
};

class Camera;

/// Listener which prints the current configuration of the given Camera Object
class PrintCameraStatusListener : public Listener {
private:
	Camera* cam;	/**< !docu pls! */
public:
	/** \brief constructor
	 *
	 * @param cam
	 */
	PrintCameraStatusListener(Camera* cam);

	/** \brief update
	 *
	 * prints the camera status to console
	 */
	void update();
};

/// Listener which sets target to value pointed at
class SetFloatValueListener : public Listener{
private:
	float* source;
	float* target;
public:
	SetFloatValueListener(float* target, float* value);
	SetFloatValueListener(float* target, float value);
	void update();
};

/// Listener which sets target to value pointed at
class SetVec3ValuesListener : public Listener{
private:
	glm::vec3* source;
	glm::vec3* target;
public:
	SetVec3ValuesListener(glm::vec3* target, glm::vec3* value);
	SetVec3ValuesListener(glm::vec3* target, glm::vec3 value);
	void update();
};

/// Listener which owns a boolean and will be set to dirty when called
class DirtyFlagListener : public Listener{
private:
	bool dirtyFlag;
public:
	DirtyFlagListener();
	void update();	/**< will set the dirtyFlag to dirty */

	bool getDirtyFlag() const;
	void setDirtyFlag(bool dirtyFlag);
};

#endif
