#include "HeightField.h"
#include <iostream>

HeightField::HeightField(char* filename, int width, int height, glm::vec3 pos){

	fileName = filename;
	mapWidth = width;
	mapHeight = height;
	position = pos;

	create();
	physicsComponent = new PhysicsComponent(filename,position.x,position.y,position.z);
}

HeightField::HeightField(char* filename, int width, int height, float x, float y, float z){

	fileName = filename;
	mapWidth = width;
	mapHeight = height;
	position = (x,y,z);

	create();
	physicsComponent = new PhysicsComponent(filename,position.x,position.y,position.z);
}

HeightField::~HeightField(){

	delete fileName;
	delete mapWidth;
	delete mapHeight;
	delete position;
	delete physicsComponent;
	delete heightMap;
}

bool HeightField::create(){

	FILE* heightfieldFile;
	heightfieldFile = fopen(fileName,"rb");
	fread(heightMap,1,mapWidth*mapHeight,heightfieldFile);
	fclose(heightfieldFile);

	return true;
}

void HeightField::render(){

	glBegin(GL_POINTS);
	for(int i=0; i<mapWidth; i++){
		for(int j=0; j<mapHeight; j++){
			glVertex3f(i,heightMap[i][j],j);
		}
	}
	glEnd();
}

