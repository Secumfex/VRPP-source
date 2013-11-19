#include "Resource.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <GLFW/glfw3.h>




//---------------RESOURCE SCOPE--------------------

void Resource :: setName(char* name){
	mName = name;

}


//---------------TEXTURE SCOPE--------------------

void Texture :: streamToVRAM(){

}

void Texture :: getResource(char* filename){

	//TODO: GLMModel machen

	//TODO: file finden und das Model damit füttern

	//TODO: MTL erkennen und subfunctions invokieren

	//TODO: Funktionen invokieren

	//TODO: Model löschen
}

//---------------MESH SCOPE--------------------

void Mesh :: streamToVRAM(){

	glGenBuffers(4, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mIndices), &mIndices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mNormals), &mNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mUVs), &mUVs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

}

void Mesh :: getResource(char* filename){
    


GLMmodel *model = glmReadOBJ(filename);

}

vector<glm::vec3> Mesh::returnMesh()
{
    return meshVertices;
}
    
	//TODO: GLMModel machen

	//TODO: file finden und das Model damit füttern

	//TODO: Alle notwendigen Daten aus dem Model lesen

	//TODO: Model löschen



