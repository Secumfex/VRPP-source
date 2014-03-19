
#ifndef HEIGHTFIELD_H_
#define HEIGHTFIELD_H_

#include <windows.h>
#include <stdio.h>
#include "Physics/PhysicsComponent.h"
#include <glm/glm.hpp>

class HeightField{
private:
	PhysicsComponent* physicsComponent;		/**< pointer to the physics component of the HeightField */
	char* fileName;							/**< filename of the heightmap image */
	int mapWidth,mapHeight;					/**< resolution of the heightmap image */
	glm::vec3 position;						/**< position of the HeightField */

public:
	BYTE heightMap[mapWidth][mapHeight];	/**< !docu pls! */

	/** \brief constructor
	 *
	 */
	HeightField(char* filename, int width , int height, glm::vec3 pos);

	/** \brief constructor
	 *
	 */
	HeightField(char* filename,int width, int height, float x, float y, float z);

	/** \brief destructor
	 *
	 */
	~HeightField();

	/** \brief creates the heightfield
	 *
	 */
	bool create();

	/** \brief draws the heightfield
	 *
	 */
	void render();
};


#endif /* HEIGHTFIELD_H_ */
