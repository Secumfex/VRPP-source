#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <vector>
#include <Visuals/Texture.h>


#include <iostream>
#include <fstream>

using namespace std;


class Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:

	//---------------MEMBER VARIABLES--------------------
private:

public:

};

class Material : public Resource {

	//---------------MEMBER FUNCTIONS--------------------
public:
	Material ();
	~Material ();

	int texCount;

	int texCount;

	void setName(std::string name);
	void setAmbient(glm::vec4 ambient);
	void setDiffuse(glm::vec4 diffuse);   //erstes basteln
	void setSpecular(glm::vec4 specular);
	void setEmission(glm::vec4 specular);
	void setShininess(GLfloat term);

	void setAmbientMap(Texture* tex);
	void setDiffuseMap(Texture* tex);
	void setSpecularMap(Texture* tex);
	void setNormalMap(Texture* tex);
	void setHeightMap(Texture* tex);
	void setShadowMap(Texture* tex);

	Texture* getAmbientMap();
	Texture* getDiffuseMap();
	Texture* getSpecularMap();
	Texture* getNormalMap();
	Texture* getHeightMap();
	Texture* getShadowMap();

	glm::vec3* getAmbient();
	glm::vec3* getDiffuse();
	glm::vec3* getSpecular();
	GLfloat getSpecularTerm();

	//---------------MEMBER VARIABLES--------------------
private:
	std::string mName;
	vector<Texture*> mTextures;

	glm::vec3 mAmbColor;
	glm::vec3 mDiffColor;
	glm::vec3 mSpecColor;
	GLfloat mSpecCoeff;




};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	Mesh();
	~Mesh();

	void streamToVRAM();
	void setVao(GLuint vao);
	GLuint getVao();



	void setUniformBlockIndex(GLuint ind);
	GLuint getUniformBlockIndex();

	void setNumFaces (int faces);
	int getNumFaces();

	void setTexIndex(int index);
	int getTexIndex();


	//---------------MEMBER VARIABLES--------------------
private:

GLuint mVaoHandle;  //gleiche wie unten "vao",  also noch anpassen. (wurde jetzt gel�scht)



// TODO set variables privat. setter&getter!

//copy from VirtualObjectFactory.h  (struct)
        GLuint uniformBlockIndex;
       // float transform[16];
       // int numIndices;
		int numFaces;
        //unsigned int type;
       // Material mat;
      //  unsigned int *indexes;
        // float *positions;
      //  float *normals;
		int texIndex;
//end of copy



};

#endif /* RESOURCE_H */
