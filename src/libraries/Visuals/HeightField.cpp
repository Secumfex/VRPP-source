#include "HeightField.h"
#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>

HeightField::HeightField(char* filename, int width, int height, glm::vec3 pos){

	fileName = filename;
	mapWidth = width;
	mapHeight = height;
	position = pos;

	loaded = false;

	load();
	//create();
	physicsComponent = new PhysicsComponent(filename,position.x,position.y,position.z);
}

HeightField::HeightField(char* filename, int width, int height, float x, float y, float z){

	fileName = filename;
	mapWidth = width;
	mapHeight = height;
	position = (x,y,z);

	loaded = false;

	load();
	//create();
	physicsComponent = new PhysicsComponent(filename,position.x,position.y,position.z);
}

HeightField::~HeightField(){

	delete fileName;
	delete mapWidth;
	delete mapHeight;
	delete position;
	delete physicsComponent;

	delete loaded;

	delete heightMap;
}

bool HeightField::load(){

	if(loaded == true){
		loaded = false;
		//release();
	}

	FILE* heightfieldFile;
	heightfieldFile = fopen(fileName,"rb");
	fread(heightMap,1,mapWidth*mapHeight,heightfieldFile);
	fclose(heightfieldFile);

	//create VBO
	glGenBuffers(1,&vboHeightMap);
	glBindBuffer(GL_ARRAY_BUFFER,vboHeightMap);

	//precalculate vertex positions and its texture coordinates
	//GLfloat vertexData[mapHeight][mapWidth*3];
	//GLfloat coordsData[mapHeight][mapWidth*2];
	vector< vector< glm::vec3> > vertexData(mapHeight, vector<glm::vec3>(mapWidth));
	vector< vector< glm::vec2> > coordsData(mapHeight, vector<glm::vec2>(mapWidth));
	//vector<glm::vec3> vertexData[mapHeight][vector<glm::vec3>(mapWidth)];
	//vector<glm::vec2> coordsData[mapHeight][vector<glm::vec2>(mapWidth)];

	//every 10 rows and every 10 columns we want to have one instance of texture
	float textureU = float(mapWidth)*0.1f;
	float textureV = float(mapHeight)*0.1f;

	int widthStep = 1;						//schrittweite
	int heightStep = widthStep*mapWidth;

	//stretch heightmap points into range <-0.5, 0.5> on X and Z axis uniformly and <0.0, 1.0> on Y axis
	for(int i=0; i<mapHeight; i++){
		for(int j=0; j<mapWidth; j++) {

			float scaleWidth = float(j)/float(mapWidth-1);
	        float scaleHeight = float(i)/float(mapHeight-1);
	        float vertexHeight = float(*(heightMap+heightStep*i+j*widthStep))/255.0f;
	        vertexData[i][j] = glm::vec3(-0.5f+scaleWidth, vertexHeight, -0.5f+scaleHeight);
	        coordsData[i][j] = glm::vec2(textureU*scaleWidth, textureV*scaleHeight);
	    }
	}

	//calculate normals. sum all normals of surrounding triangles, then normalize final vector
	vector< vector<glm::vec3> > normals[2];
	for(int i=1; i<2; i++){
		normals[i] = vector< vector<glm::vec3> >(mapHeight-1, vector<glm::vec3>(mapWidth-1));
	}

	//calculate normals of each triangle (one quad contains 2 triangles)
	for(int i=0; i<mapHeight-1; i++){
	    for(int j=0; j<mapWidth-1; j++){

	        glm::vec3 triangle0[] = {vertexData[i][j],
	        						  vertexData[i+1][j],
	        						  vertexData[i+1][j+1]};
	        glm::vec3 triangle1[] = {vertexData[i+1][j+1],
	        						  vertexData[i][j+1],
	        						  vertexData[i][j]};

	        glm::vec3 triangleNormal0 = glm::cross(triangle0[0]-triangle0[1], triangle0[1]-triangle0[2]);
	        glm::vec3 triangleNormal1 = glm::cross(triangle1[0]-triangle1[1], triangle1[1]-triangle1[2]);

	        normals[0][i][j] = glm::normalize(triangleNormal0);
	        normals[0][i][j] = glm::normalize(triangleNormal1);
	    }
	}

	//calculate final normals
	vector< vector<glm::vec3> > finalNormals = vector< vector<glm::vec3> >(mapHeight, vector<glm::vec3>(mapWidth));

	for(int i=0; i<mapHeight; i++){
		for(int j=0; j<mapWidth; j++){

			glm::vec3 finalNormal = glm::vec3(0.0f, 0.0f, 0.0f);

			// look for upper-left triangles
			if(j != 0 && i != 0){
				for(int k=0; k<2; k++){
					finalNormal += normals[k][i-1][j-1];
				}
			}
			//look for upper-right triangles
			if(i != 0 && j != mapWidth-1){
				finalNormal += normals[0][i-1][j];
			}
			//look for bottom-right triangles
			if(i != mapHeight-1 && j != mapWidth-1){
				for(int k=0; k<2; k++){
					finalNormal += normals[k][i][j];
				}
			}
			// Look for bottom-left triangles
			if(i != mapHeight-1 && j != 0){
				finalNormal += normals[1][i][j-1];
			}
			finalNormal = glm::normalize(finalNormal);
			//store final normal of j-th vertex in i-th row
			finalNormals[i][j] = finalNormal;
		}
	}

	//adding data vertex-by-vertex to our first VBO
	//create VBO
	glGenBuffers(1,&vboHeightMap);
	glBindBuffer(GL_ARRAY_BUFFER,vboHeightMap);

	//fill VBO with vertex data
	/*
	for(int i=0; i<mapHeight; i++){
		for(int j=0; j<mapWidth; j++){
			vboHeightMap.AddData(&vertexData[i][j], sizeof(glm::vec3)); // Add vertex
	        vboHeightMap.AddData(&vCoordsData[i][j], sizeof(glm::vec2)); // Add tex. coord
	        vboHeightMap.AddData(&vFinalNormals[i][j], sizeof(glm::vec3)); // Add normal
		}
	}
	*/
	//add Data
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);

	//second VBO that stores indices
	//create VBO
	glGenBuffers(1,&iboHeightMap);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iboHeightMap);

	int primitiveRestartIndex = mapHeight*mapWidth;
	/*
	for(int i=0; i<mapHeight-1; i++){
		for(int j=0; j<mapWidth; j++){
			for(int k; k<2; k++){
				int height = i+(1-k);
		        int index = height*mapWidth+j;
		        vboHeightmapIndices.AddData(&index, sizeof(int));
		        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

			}
		}
	    // Restart triangle strips
	    vboHeightmapIndices.AddData(&iPrimitiveRestartIndex, sizeof(int));
	}
	*/
	//add Data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);	//TODO: Indices aendern

	//TODO: anpassen auf "normales" glBind/glGen/etc., ohne verwendung der lib aus tutorial
	/*
	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);
	// Attach vertex data to this VAO
	vboHeightmapData.BindVBO();
	vboHeightmapData.UploadDataToGPU(GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2*sizeof(glm::vec3)+sizeof(glm::vec2), (void*)(sizeof(glm::vec3)+sizeof(glm::vec2)));

	// And now attach index data to this VAO
	// Here don't forget to bind another type of VBO - the element array buffer, or simplier indices to vertices
	vboHeightmapIndices.BindVBO(GL_ELEMENT_ARRAY_BUFFER);
	vboHeightmapIndices.UploadDataToGPU(GL_STATIC_DRAW);
	*/

	loaded = true;
	return true;
}

/*
bool HeightField::create(){

	FILE* heightfieldFile;
	heightfieldFile = fopen(fileName,"rb");
	fread(heightMap,1,mapWidth*mapHeight,heightfieldFile);
	fclose(heightfieldFile);

	return true;
}
*/

void HeightField::render(){

	glBegin(GL_POINTS);
	for(int i=0; i<mapWidth; i++){
		for(int j=0; j<mapHeight; j++){
			glVertex3f(i,heightMap[i][j],j);
		}
	}
	glEnd();
}

