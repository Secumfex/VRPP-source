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
	 static std::vector<struct MyMesh> myMeshes;

	 // ebenfalls aus dem fix
	static std::map<std::string, GLuint> textureIdMap;	



//---------------MEMBER FUNCTIONS--------------------
public:

	static void hello();

	//eingef�gt
static	void set_float4(float f[4], float a, float b, float c, float d);
static	void color4_to_float4(const aiColor4D *c, float f[4]);


VirtualObject* createVirtualObject();
VirtualObject* createVirtualObject(std::string filename);
VirtualObject* createVirtualObject(vector<GraphicsComponent*> graphcomps);
VirtualObject* copyVirtualObject(VirtualObject vo);


};

#endif /* VIRTUALOBJECTFACTORY_H_ */
