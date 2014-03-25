/* auskommentiert fuer "one step back"-commit
#ifndef HEIGHTFIELD_H_
#define HEIGHTFIELD_H_

#include <windows.h>
#include <stdio.h>
#include "Physics/PhysicsComponent.h"
#include <glm/glm.hpp>

class HeightField{
private:
	PhysicsComponent* physicsComponent;		/**< pointer to the physics component of the HeightField */
	/* auskommentiert fuer "one step back"-commit
	char* fileName;							/**< filename of the heightmap image */
	/* auskommentiert fuer "one step back"-commit
	static int mapWidth,mapHeight;					/**< resolution of the heightmap image */
	/* auskommentiert fuer "one step back"-commit
	glm::vec3 position;						/**< position of the HeightField */
	/* auskommentiert fuer "one step back"-commit
	bool loaded;
	GLuint vboHeightMap;
	GLuint iboHeightMap;

public:
	BYTE heightMap[mapWidth][mapHeight];	/**< !docu pls! */

	/** \brief constructor
	 *
	 */
	/* auskommentiert fuer "one step back"-commit
	HeightField(char* filename, int width , int height, glm::vec3 pos);

	/** \brief constructor
	 *
	 */
	/* auskommentiert fuer "one step back"-commit
	HeightField(char* filename,int width, int height, float x, float y, float z);

	/** \brief destructor
	 *
	 */
	/* auskommentiert fuer "one step back"-commit
	~HeightField();

	/** \brief load the heightfield
	 *
	 * !docu pls!
	 */
	/* auskommentiert fuer "one step back"-commit
	bool load();

	/** \brief creates the heightfield
	 *
	 */
	/*
	bool create();
	*/

	/** \brief draws the heightfield
	 *
	 */
	/* auskommentiert fuer "one step back"-commit
	void render();
};


#endif /* HEIGHTFIELD_H_ */
