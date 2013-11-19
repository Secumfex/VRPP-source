#include "Resource.h"


//---------------MESH SCOPE--------------------

void Resource :: setName(const char* name){
	mName = name;

}


//---------------MESH SCOPE--------------------

void Texture :: streamToVRAM(){

}

void Texture :: getResource(const char* filename){

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mNormals), mNormals, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mUVs), mUVs, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


}

void Mesh :: getResource(const char* filename){

	//TODO: GLMModel machen

	//TODO: file finden und das Model damit füttern

	//TODO: Alle notwendigen Daten aus dem Model lesen

	//TODO: Model löschen
}


