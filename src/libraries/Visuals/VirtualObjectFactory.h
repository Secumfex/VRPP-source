/*
 * VirtualObjectFactory.h
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#ifndef VIRTUALOBJECTFACTORY_H_
#define VIRTUALOBJECTFACTORY_H_

#include <Patterns/Singleton.h>
#include <Visuals/VirtualObject.h>
#include <vector>

using namespace std;

class VirtualObjectFactory : public Singleton<VirtualObjectFactory> {
	friend class Singleton<VirtualObjectFactory>;
//---------------MEMBER VARIABLES--------------------

	  struct MyMesh{
        GLuint vao;
        GLuint texUnits[MAX_TEXTURES];
        GLuint texTypes[MAX_TEXTURES];
        GLuint uniformBlockIndex;
        float transform[16];
        int numIndices;
		int numFaces;
        unsigned int type;
        struct Material mat;
        unsigned int *indexes;
        float *positions;
        float *normals;
    };

	  struct MyMaterial{

	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	float shininess;
	int texCount;
};



//---------------MEMBER FUNCTIONS--------------------
public:

	static void hello();

static VirtualObject* createVirtualObject();
static VirtualObject* createVirtualObject(std::string filename);
static VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);
static VirtualObject* copyVirtualObject(VirtualObject vo);

};

#endif /* VIRTUALOBJECTFACTORY_H_ */
