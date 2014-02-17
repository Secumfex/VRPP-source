/*#include "Patterns/Listener.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <cmath>

//Listener which changes the ClearColor by a tiny bit on every update
class AnimateClearColorListener : public Listener{
private:
	float t;
public:
	AnimateClearColorListener(){t = 0.0;}
	void update(){
		float r = std::sin(1.0*t) * 0.5;
		float g = std::sin(2.0*t+0.3) * 0.5;
		float b = std::sin(3.0*t+0.7) * 0.5;
		glClearColor(r,g,b,1.0);
		t+= 0.0001;
	}
};*/