#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>

// #include "assimp/Importer.hpp"
// #include "assimp/postprocess.h"
// #include "assimp/scene.h"

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
	/** \brief default constructor
	 *
	 */
	Material ();

	/** \brief destructor
	 *
	 */
	~Material ();



	/** \brief setter
	 *
	 * sets name
	 * @param name
	 */
	void setName(std::string name);

	/** \brief setter
	 *
	 * sets ambient color
	 * @param ambient
	 */
	void setAmbient(glm::vec3 ambient);

	/** \brief setter
	 *
	 * sets diffuse color
	 * @param diffuse
	 */
	void setDiffuse(glm::vec3 diffuse);

	/** \brief setter
	 *
	 * sets specular color
	 * @param specular
	 */
	void setSpecular(glm::vec3 specular);

	/** \brief setter
	 *
	 * sets emissive color
	 * @param emission
	 */
	void setEmission(glm::vec3 emission);

	/** \brief setter
	 *
	 * sets shininess
	 * @param term
	 */
	void setShininess(GLfloat term);

	/** \brief setter
	 *
	 * sets amount of transparancy
	 * @param term
	 */
	void setTransparency(GLfloat term);

	/** \brief setter
	 *
	 * sets ambient texture
	 * @param tex
	 */
	void setAmbientMap(Texture* tex);

	/** \brief setter
	 *
	 * sets diffuse texture
	 * @param tex
	 */
	void setDiffuseMap(Texture* tex);

	/** \brief setter
	 *
	 * sets emissive texture
	 * @param tex
	 */
	void setEmissiveMap(Texture* tex);

	/** \brief setter
	 *
	 * sets normal texture
	 * @param tex
	 */
	void setNormalMap(Texture* tex);

	/** \brief setter
	 *
	 * sets height texture
	 * @param tex
	 */
	void setHeightMap(Texture* tex);

	/** \brief setter
	 *
	 * sets opacity texture
	 * @param tex
	 */
	void setOpacityMap(Texture* tex);

	/** \brief setter
	 *
	 * sets specular texture
	 * @param tex
	 */
	void setSpecularMap(Texture* tex);

	/** \brief setter
	 *
	 * sets reflecting texture
	 * @param tex
	 */
	void setReflectionMap(Texture* tex);

	/** \brief setter
	 *
	 * sets shining texture
	 * @param tex
	 */
	void setShininessMap(Texture* tex);

	/** \brief setter
	 *
	 * @param tex
	 */
	void setDisplacementMap(Texture* tex);

	/** \brief setter
	 *
	 * @param tex
	 */
	void setLightMap(Texture* tex);


	/** \brief getter
	 *
	 * @return ambient texture
	 */
	Texture* getAmbientMap();

	/** \brief getter
	 *
	 * @return diffuse texture
	 */
	Texture* getDiffuseMap();

	/** \brief getter
	 *
	 * @return emissive texture
	 */
	Texture* getEmissiveMap();

	/** \brief getter
	 *
	 * @return normal texture
	 */
	Texture* getNormalMap();

	/** \brief getter
	 *
	 * @return height texture
	 */
	Texture* getHeightMap();

	/** \brief getter
	 *
	 * @return opacity texture
	 */
	Texture* getOpacityMap();


	/** \brief getter
	 *
	 * @return specular texture
	 */

	Texture* getSpecularMap();

	/** \brief getter
	 *
	 * @return reflection texture
	 */
	Texture* getReflectionMap();

	/** \brief getter
	 *
	 * @return shining texture
	 */
	Texture* getShininessMap();

	/** \brief getter
	 *
	 * @return
	 */
	Texture* getDisplacementMap();

	/** \brief getter
	 *
	 * @return
	 */
	Texture* getLightMap();


	/** \brief getter
	 *
	 * @return ambient color
	 */
	glm::vec3 getAmbient();

	/** \brief getter
	 *
	 * @return diffuse color
	 */
	glm::vec3 getDiffuse();

	/** \brief getter
	 *
	 * @return specular color
	 */
	glm::vec3 getSpecular();

	/** \brief getter
	 *
	 * @return emissive color
	 */
	glm::vec3 getEmission();

	/** \brief getter
	 *
	 * @return shininess value
	 */
	GLfloat getShininess();

	/** \brief getter
	 *
	 * @return transparancy value
	 */
	GLfloat getTransparency();

	/** \brief getter
	 *
	 * @return name
	 */
	std::string getName();


	/** \brief checks wheather there's a normal texture or not
	 *
	 * @return true or false
	 */
	bool hasNormalTexture();

	/** \brief checks wheather there's a diffuse texture or not
	 *
	 * @return true or false
	 */
	bool hasDiffuseTexture();

	/** \brief checks wheather there's a ambient texture or not
	 *
	 * @return true or false
	 */
	bool hasAmbientTexture();

	/** \brief checks wheather there's a emissive texture or not
	 *
	 * @return true or false
	 */
	bool hasEmissiveTexture();

	/** \brief checks wheather there's a height texture or not
	 *
	 * @return true or false
	 */
	bool hasHeightTexture();

	/** \brief checks wheather there's a opacity texture or not
	 *
	 * @return true or false
	 */
	bool hasOpacityTexture();

	/** \brief checks wheather there's a specular texture or not
	 *
	 * @return true or false
	 */
	bool hasSpecularTexture();

	/** \brief checks wheather there's a reflection texture or not
	 *
	 * @return true or false
	 */
	bool hasReflectionTexture();

	/** \brief checks wheather there's a shininess texture or not
	 *
	 * @return true or false
	 */
	bool hasShininessTexture();

	/** \brief checks wheather there's a displacement texture or not
	 *
	 * @return true or false
	 */
	bool hasDisplacementTexture();

	/** \brief checks wheather there's a light texture or not
	 *
	 * @return true or false
	 */
	bool hasLightTexture();




	//---------------MEMBER VARIABLES--------------------
private:
	std::string mName;			/**< docu pls */
	vector<Texture*> mTextures;	/**< docu pls */


	glm::vec3 mAmbColor;		/**< docu pls */
	glm::vec3 mDiffColor;		/**< docu pls */
	glm::vec3 mSpecColor;		/**< docu pls */
	glm::vec3 mEmissColor;		/**< docu pls */

	GLfloat mShininess;			/**< docu pls */
    GLfloat mTransparency;		/**< docu pls */


};

class Mesh : public Resource{

	//---------------MEMBER FUNCTIONS--------------------
public:
	/** \brief constructor
	 *
	 */
	Mesh();

	/** \brief destructor
	 *
	 */
	~Mesh();


	/** \brief setter
	 *
	 * sets VAO
	 * @param vao
	 */
	void setVAO(GLuint vao);

	/** \brief getter
	 *
	 * @return VAO
	 */
	GLuint getVAO();


	/** \brief setter
	 *
	 * sets number of faces
	 * @param faces
	 */
	void setNumFaces(int faces);

	/** \brief getter
	 *
	 * @return number of faces
	 */
	int getNumFaces();


	/** \brief setter
	 *
	 * sets number of vertices
	 * @param verts
	 */
	void setNumVertices(int verts);

	/** \brief getter
	 *
	 * @return number of vertices
	 */
	int getNumVertices();


	/** \brief setter
	 *
	 * sets number of indices
	 * @param verts
	 */
	void setNumIndices(int verts);

	/** \brief getter
	 *
	 * @return number of indices
	 */
	int getNumIndices();


	/** \brief setter
	 *
	 * sets an array of vertex positions
	 * @param position
	 */
	void setVertexPosition(std::vector<glm::vec3> position);

	/** \brief getter
	 *
	 * @return list of vertices
	 */
	std::vector<glm::vec3> getVertices();

	/** \brief add boneweight
	 *
	 * @param boneweight list of bufferhandles for bone weights
	 */
	void addBoneWeight(GLuint boneweight);


	/** \brief setter
	 *
	 * sets the center of mass model matrix offset
	 * @param offsetMatrix (translational matrix to move the center of mass into the local model space origin)
	 */
	void setCenterOfMassOffsetMatrix(glm::mat4 offsetMatrix);

	const glm::mat4& getCenterOfMassOffsetMatrix() const;

	//---------------MEMBER VARIABLES--------------------
private:

		GLuint mVaoHandle; 		/**< !docu pls! */	 //gleiche wie unten "vao",  also noch anpassen. (wurde jetzt gel�scht)

		int mNumFaces;			/**< !docu pls! */
		int mNumVerts;			/**< !docu pls! */
		int mNumIndices;		/**< !docu pls! */

		std::vector<glm::vec3> mVertexPositions;	/**< !docu pls! */

		std::vector<GLuint> mBoneWeights;			/**< !docu pls! */

		glm::mat4 mCenterOfMassOffsetMatrix;	/**< offset of the center of mass in relation to the local coordinates origin */

};

#endif /* RESOURCE_H */
