/*
 * VirtualObjectFactory.h
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#ifndef VIRTUALOBJECTFACTORY_H_
#define VIRTUALOBJECTFACTORY_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Patterns/Singleton.h>
#include <Visuals/VirtualObject.h>
#include "MaterialManager.h"
#include <vector>
#include <Tools/NoAssimpVirtualObjectFactory.h>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

using namespace std;

class VirtualObjectFactory : public Singleton<VirtualObjectFactory> {
	friend class Singleton<VirtualObjectFactory>;
//---------------MEMBER VARIABLES--------------------






	  struct MyMesh{
        GLuint vao;
		//wurde im fix einfach weggelassen. jedoch wurde auch devil benutzt, kenne noch keinen zusammenhang
		/*
        GLuint texUnits[MAX_TEXTURES];
        GLuint texTypes[MAX_TEXTURES];
		*/

        GLuint uniformBlockIndex;
        float transform[16];
        int numIndices;
		int numFaces;
        unsigned int type;

        Material mat;
        unsigned int *indexes;
        float *positions;
        float *normals;
		int texIndex;
    };

	
	//auch dazu gebastelt. okay, dass es static ist??
std::vector<struct MyMesh> myMeshes;

	 // ebenfalls aus dem fix

std::map<std::string, GLuint> textureIdMap;

VirtualObject* mCube;
GraphicsComponent* mScreenFillTriangle;


//---------------MEMBER FUNCTIONS--------------------
public:



VirtualObject* createNonAssimpVO();
GraphicsComponent* getTriangle();

VirtualObject* createVirtualObject();
VirtualObject* createVirtualObject(std::string filename);
VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);
VirtualObject* copyVirtualObject(VirtualObject vo);

private:

void set_float4(float f[4], float a, float b, float c, float d);
void color4_to_float4(const aiColor4D *c, float f[4]);
};

#endif /* VIRTUALOBJECTFACTORY_H_ */
