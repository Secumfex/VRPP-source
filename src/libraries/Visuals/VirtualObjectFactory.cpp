/*

 * VirtualObjectFactory.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/VirtualObjectFactory.h>
#include <string>

#ifndef PI
	#define PI  3.14159265359
#endif


VirtualObjectFactory::VirtualObjectFactory(){
	mCube = NULL;
	mScreenFillTriangle = NULL;
	mQuad = NULL;
}

//eingefügt

void VirtualObjectFactory::set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void VirtualObjectFactory::color4_to_float4(const aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

GraphicsComponent* VirtualObjectFactory::getTriangle(){
	if(mScreenFillTriangle == NULL){

		Mesh *triangle = new Mesh;
		Material *mat = new Material();
		mat->setName("screenfill_triangle");
		GLuint screenFillVertexArrayHandle;

		glGenVertexArrays(1, &screenFillVertexArrayHandle);
		glBindVertexArray(screenFillVertexArrayHandle);

		GLuint indexBufferHandle;
		glGenBuffers(1, &indexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);

		GLint indices[] = {0, 1, 2};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint vertexBufferHandle;
		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);

		GLfloat vertices[] = {-1, -1,   3, -1,   -1,  3};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		triangle->setVAO(screenFillVertexArrayHandle);
		triangle->setNumIndices(3);
		triangle->setNumVertices(3);
		triangle->setNumFaces(1);

		GraphicsComponent *gc = new GraphicsComponent(triangle, mat);
		mScreenFillTriangle = gc;

	} return mScreenFillTriangle;
}

GraphicsComponent* VirtualObjectFactory::getQuad(){
	if (mQuad == NULL){
		Mesh* quadMesh = new Mesh();
		Material* quadMat = new Material();

		quadMat->setName("default_quad_material");
		GLuint quadVertexArrayHandle;

		glGenVertexArrays(1, &quadVertexArrayHandle);
		glBindVertexArray(quadVertexArrayHandle);

		//we generate multiple buffers at a time
		GLuint vertexBufferHandles[5];
		glGenBuffers(4, vertexBufferHandles);

		int indices[] = {0, 1, 2, 2, 3, 0};

	    float size = 0.5;

	    GLfloat positions[] = {
	        -size,-size, 0.0f,   size,-size, 0.0f,   size, size, 0.0f,   -size, size, 0.0f
	    };

	    GLfloat normals[] = {
	        0.0,  0.0,  1.0,    0.0,  0.0,  1.0,    0.0,  0.0,  1.0,   0.0,  0.0,  1.0
	    };

	    GLfloat tangents[] = {
	        0.0, -1.0,  0.0,    0.0, -1.0,  0.0,    0.0, -1.0,  0.0,    0.0, -1.0,  0.0
	    };

	    GLfloat uvCoordinates[] = {
	        0,0, 1,0, 1,1,  0,1
	    };

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoordinates), uvCoordinates, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandles[4]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tangents), tangents, GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferHandles[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		quadMesh->setVAO(quadVertexArrayHandle);
		quadMesh->setNumIndices(6);
		quadMesh->setNumVertices(4);
		quadMesh->setNumFaces(2);

		mQuad = new GraphicsComponent(quadMesh, quadMat);
	}
	return mQuad;
}

VirtualObject* VirtualObjectFactory::createNonAssimpVO(float mass){

	if(mCube == NULL){
		NoAssimpVirtualObjectFactory *voFactory = new NoAssimpVirtualObjectFactory();
		mCube = voFactory->createCubeObject(mass);
	}

	return mCube;
}



VirtualObject* VirtualObjectFactory::createVirtualObject(){
	return new VirtualObject();
}

VirtualObject* VirtualObjectFactory::createVirtualObject(std::string filename, BodyType bodyType, float mass, int collisionFlag, bool blenderAxes)
{
	VirtualObject* virtualObject = new VirtualObject();

	Assimp::Importer Importer;
	//TextureManager* texManager = TextureManager::getInstance();

	std::string directory = filename.substr( filename.find_last_of( '/' ) + 1 );
    std::string objName = directory;
	directory = filename.substr(0, filename.length() - directory.length());

	using namespace std;


	//looking up the file

	std::ifstream fin(filename.c_str());
	if(!fin.fail()) {
		fin.close();
	}
	else{

		cout<<"Couldn't open file: " << filename.c_str()<<endl;
		cout<<Importer.GetErrorString()<<endl;
		cout<<"Have a cube instead!"<<endl;

		return createNonAssimpVO();
	}

	const aiScene* pScene = Importer.ReadFile( filename,
			aiProcess_Triangulate |
			aiProcess_GenSmoothNormals|
			aiProcess_GenUVCoords |
			aiProcess_FlipUVs|
			aiProcess_ValidateDataStructure |
			aiProcess_CalcTangentSpace

	);

	// Melden, falls der Import nicht funktioniert hat
	if( !pScene)
	{
		cout<<Importer.GetErrorString()<<endl;
		return createNonAssimpVO();
	}

	cout<<"Import of scene " <<filename.c_str()<<" succeeded."<<endl;

	glm::vec3 physics_min = glm::vec3(FLT_MAX,FLT_MAX,FLT_MAX);
	glm::vec3 physics_max = glm::vec3(-FLT_MAX,-FLT_MAX,-FLT_MAX);

	// For each mesh

	for (unsigned int n = 0; n < pScene->mNumMeshes; ++n)
	{
		const aiMesh* mesh = pScene->mMeshes[n];


		//Our Material and Mash to be filled
		Mesh* aMesh = new Mesh();
		Material* aMat = new Material();


		GLuint buffer = 0;
		glm::vec3 aabbMax = glm::vec3(INT_MIN, INT_MIN, INT_MIN);
		glm::vec3 aabbMin = glm::vec3(INT_MAX, INT_MAX, INT_MAX);


		//Our Indices for our Vertexlist
		vector<unsigned int> indices;

		int incidesCounter = 0;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			unsigned int i=0;
			for (i = 0; i < mesh->mFaces[t].mNumIndices; ++i) {
				indices.push_back(mesh->mFaces[t].mIndices[i]);
				incidesCounter++;
			}
		}

		aMesh->setNumVertices(mesh->mNumVertices);
		aMesh->setNumIndices(mesh->mNumFaces * 3);


		// hier wurde aMesh.numFaces in dem Struct erstellt (VirtualObjectFactory.h)

		aMesh->setNumFaces(pScene->mMeshes[n]->mNumFaces);

		// generate Vertex Array for mesh
		GLuint temp = 0;
		glGenVertexArrays(1,&temp);
		aMesh->setVAO(temp);
		glBindVertexArray(aMesh->getVAO());


		// buffer for faces (indices)
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

		// buffer for vertex positions
		if (mesh->HasPositions()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);

			//vertexLoc wurde hier ersetzt
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

		}

		// buffer for vertex normals
		if (mesh->HasNormals()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);

			// normalLoc wurde hier ersetzt
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);


		}
		if (mesh->HasTangentsAndBitangents()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mTangents, GL_STATIC_DRAW);

			// normalLoc wurde hier ersetzt
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);

		}
		if(mesh->HasBones()){
			cout << "HAT ANIMATION"<< endl;
		}

		// buffer for vertex texture coordinates
		vector <float>texCoords;
		float uv_steps = 1.0 / mesh->mNumVertices;

		if (mesh->HasTextureCoords(0)){
			for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
				texCoords.push_back(mesh->mTextureCoords[0][k].x);
				texCoords.push_back(mesh->mTextureCoords[0][k].y);
			}
		}
		else
		{
			for(unsigned int k = 0; k < mesh->mNumVertices; ++k){
				texCoords.push_back(k * uv_steps);
				texCoords.push_back(k * uv_steps);

			}
		}
		std::vector<glm::vec3> vertexPositions;
		for(unsigned int k = 0; k < mesh->mNumVertices; ++k){
			if(aabbMax.x < mesh->mVertices[k].x)
				aabbMax.x = mesh->mVertices[k].x;
			if(aabbMax.y < mesh->mVertices[k].y)
				aabbMax.y = mesh->mVertices[k].y;
			if(aabbMax.z < mesh->mVertices[k].z)
				aabbMax.z = mesh->mVertices[k].z;
			if(aabbMin.x > mesh->mVertices[k].x)
				aabbMin.x = mesh->mVertices[k].x;
			if(aabbMin.y > mesh->mVertices[k].y)
				aabbMin.y = mesh->mVertices[k].y;
			if(aabbMin.z > mesh->mVertices[k].z)
				aabbMin.z = mesh->mVertices[k].z;

			vertexPositions.push_back(glm::vec3(mesh->mVertices[k].x, mesh->mVertices[k].y, mesh->mVertices[k].z));
		}
		aMesh->setVertexPosition(vertexPositions);


		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*mesh->mNumVertices, &texCoords[0], GL_STATIC_DRAW);
        
		//und texCoordLoc wurde dann auch ersetzt
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);


		// unbind buffers
		glBindVertexArray(0);

		// create material uniform buffer
		aiMaterial *mtl = pScene->mMaterials[mesh->mMaterialIndex];
    

		aiString texPath;   //contains filename of texture

		Texture *tex_temp = new Texture();



		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath)){
			cout << "Try to find DiffuseMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
            aMat->setDiffuseMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_AMBIENT, 0, &texPath)){
			cout << "Try to find AmbientMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setAmbientMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_OPACITY, 0, &texPath)){
			cout << "Try to find OpacityMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setOpacityMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_NORMALS, 0, &texPath)){
			//For some Reason HeightMap and NormalMap are switched in Assimp
			cout << "Try to find NormalMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setNormalMap(tex_temp);
		}
		// @todo : find out whether it really is switched or not
		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_HEIGHT, 0, &texPath)){
			//For some Reason HeightMap and NormalMap are switched in Assimp
			cout << "Try to find HeightMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setHeightMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_EMISSIVE, 0, &texPath)){
			cout << "Try to find EmissiveMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setEmissiveMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_SPECULAR, 0, &texPath)){
			cout << "Try to find SpecularMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setSpecularMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_REFLECTION, 0, &texPath)){
			cout << "Try to find ReflectionMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setReflectionMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_SHININESS, 0, &texPath)){
			cout << "Try to find ShininessMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setShininessMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DISPLACEMENT, 0, &texPath)){
			cout << "Try to find DisplacementMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setDisplacementMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_LIGHTMAP, 0, &texPath)){
			cout << "Try to find LightMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setLightMap(tex_temp);
		}

        aiString name;
		if(AI_SUCCESS == aiGetMaterialString(mtl, AI_MATKEY_NAME, &name)){
			std::string matName = name.C_Str();
			matName = matName.substr( matName.find_last_of( '/' ) + 1 );


            std::cout<<"\nName des Materials: "<<matName<<endl;

			aMat->setName(matName);
		}
        else{
			aMat->setName("genericMaterial");
        }
        
        
        /* try to generate material by name */
        
		GraphicsComponent* gc=new GraphicsComponent(aMesh,aMat);
        MaterialManager* mm= MaterialManager::getInstance();



        if(aMat->getName().find("custom") != std::string::npos)
        {
        	cout<<"\nRead from mtl\n";

	        float c[4];
	        
	 		// diffuse
			set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
			aiColor4D diffuse;
			if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse)){
			color4_to_float4(&diffuse, c);
			}
			aMat->setDiffuse(glm::vec3(c[0], c[1], c[2]));


	        // ambient
			set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
			aiColor4D ambient;
			if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
				color4_to_float4(&ambient, c);
			//memcpy(aMat.ambient, c, sizeof(c));
			aMat->setAmbient(glm::vec3(ambient.r, ambient.g, ambient.b));

	        // specular

			set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);

			aiColor4D specular;
			if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
				color4_to_float4(&specular, c);
			//memcpy(aMat.specular, c, sizeof(c));
			aMat->setSpecular(glm::vec3(specular.r, specular.g, specular.b));

	        // emission
			set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
			aiColor4D emission;
			if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
				color4_to_float4(&emission, c);
	        //memcpy(aMat.emissive, c, sizeof(c));
			aMat->setEmission(glm::vec3(emission.r, emission.g, emission.b));

	        // shininess
	        float shininess = 0.0;
			//unsigned int max;
			if(AI_SUCCESS != mtl->Get(AI_MATKEY_SHININESS, shininess))
				shininess = 50.0;


			aMat->setShininess(1.0f);
			//shininess/1000.0f
        }
        else{
	        try {
	            mm->makeMaterial(aMat->getName(),gc);
	            }
	        catch (string param){
	           cout<<"\nFAILED: generate material by name";
	            }
        }

		//Mesh und Material wird gelesen und in neuer GraphicsComponent gespeichert
		gc->setGhostObject(aabbMin, aabbMax);

		virtualObject->addGraphicsComponent(gc);

		if(aabbMin.x < physics_min.x)
		 	physics_min.x = aabbMin.x;
		 if(aabbMin.y < physics_min.y)
		 	physics_min.y = aabbMin.y;
		 if(aabbMin.z < physics_min.z)
		 	physics_min.z = aabbMin.z;
		 if(aabbMax.x > physics_max.x)
		 	physics_max.x = aabbMax.x;
		 if(aabbMax.y > physics_max.y)
		 	physics_max.y = aabbMax.y;
		 if(aabbMax.z > physics_max.z)
		 	physics_max.z = aabbMax.z;
	}

	glm::vec3 boxValue = physics_max - physics_min;
	float width = boxValue.x;
	float height = boxValue.y;
	float depth = boxValue.z;

	float x = physics_min.x + width / 2.0f;
	float y = physics_min.y + height / 2.0f;
	float z = physics_min.z + depth / 2.0f;

	glm::vec3 normal;
	normal.x= physics_min.y*physics_max.z - physics_min.z*physics_max.y;
	normal.y= physics_min.z*physics_max.x - physics_min.x*physics_max.z;
	normal.z= physics_min.x*physics_max.y - physics_min.y*physics_max.x;

//	std::cout << "max: " << physics_max.x << " , "<< physics_max.y << " , "<< physics_max.z << std::endl;
//	std::cout << "min: " << physics_min.x << " , "<< physics_min.y << " , "<< physics_min.z << std::endl;

	switch(bodyType)
	{
		case CUBE:		virtualObject->setPhysicsComponent(width, height, depth, x, y, z, mass, collisionFlag);
			break;
		case PLANE:		virtualObject->setPhysicComponent(x, y, z, normal, mass, collisionFlag);
			break;
		case SPHERE:	virtualObject->setPhysicsComponent((physics_max.x-physics_min.x)/2.0, (physics_max.x-physics_min.x)/2.0+physics_min.x, (physics_max.y-physics_min.y)/2.0+physics_min.y, (physics_max.z-physics_min.z)/2.0+physics_min.z, mass, collisionFlag);
			break;
		case OTHER:		virtualObject->setPhysicsComponent(physics_min, physics_max, mass, collisionFlag);
			break;
	}

	/******************************************************/
	std::cout << "BLENDER FILE ... :" << blenderAxes << std::endl;
	if (blenderAxes)
	{
		std::cout << "BLENDER FILE... rotating Object..." << std::endl;
		btRigidBody* rigidBody = virtualObject->getPhysicsComponent()->getRigidBody();
		btMotionState* motion = rigidBody->getMotionState();

		btTransform worldTrans;
		worldTrans.setIdentity();
		worldTrans.setRotation( btQuaternion( btVector3(1.0f, 0.0f, 0.0f), ( (-1.0f) * PI ) / 2.0f));
		std::cout << "BLENDER FILE... updating ModelMatrix" << std::endl;

		motion->setWorldTransform(worldTrans);

		virtualObject->updateModelMatrixViaPhysics();
	}
	/******************************************************/
	return virtualObject;
}

VirtualObject* VirtualObjectFactory::createVirtualObject(vector<GraphicsComponent*> graphcomps){
	VirtualObject* virtualObject = new VirtualObject();
	//TODO: alle GraphicsComponents werden an das VO übergeben

	return virtualObject;
}
