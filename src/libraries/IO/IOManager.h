#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <glm/glm.hpp>

class IOManager{

private:
	glm::mat4 mViewMatrix;
public:
	glm::mat4 getViewMatrix();
};

#endif
