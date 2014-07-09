/*

 * VirtualObjectFactory.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/VirtualObjectFactory.h>
#include <string>
#include <glm/gtx/transform.hpp>

#ifndef PI
#define PI  3.14159265359
#endif

VirtualObjectFactory::VirtualObjectFactory() {
	mCube = 0;
	mScreenFillTriangle = 0;
	mQuad = 0;
	mHalfScreenQuadLeft = 0;
	mHalfScreenQuadRight = 0;
	mDefaultBone = new Bone();
	mDefaultAnimation = new AnimationLoop();
}

//eingefügt

void VirtualObjectFactory::set_float4(float f[4], float a, float b, float c,
		float d) {
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void VirtualObjectFactory::color4_to_float4(const aiColor4D *c, float f[4]) {
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

GraphicsComponent* VirtualObjectFactory::getTriangle() {
	if (mScreenFillTriangle == 0) {

		Mesh *triangle = new Mesh;
		Material *mat = new Material();
		mat->setName("screenfill_triangle");
		GLuint screenFillVertexArrayHandle;

		glGenVertexArrays(1, &screenFillVertexArrayHandle);
		glBindVertexArray(screenFillVertexArrayHandle);

		GLuint indexBufferHandle;
		glGenBuffers(1, &indexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);

		GLint indices[] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);

		GLuint vertexBufferHandle;
		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);


		GLfloat vertices[] = {-1.0f, -1.0f,   3.0f, -1.0f,   -1.0f,  3.0f};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		triangle->setVAO(screenFillVertexArrayHandle);
		triangle->setNumIndices(3);
		triangle->setNumVertices(3);
		triangle->setNumFaces(1);

		GraphicsComponent *gc = new GraphicsComponent(triangle, mat);
		mScreenFillTriangle = gc;

	}
	return mScreenFillTriangle;
}

GraphicsComponent* VirtualObjectFactory::getHalfScreenQuad(HalfScreen side) {
	if (mHalfScreenQuadLeft == 0 || mHalfScreenQuadRight == 0) {

		std::cout << " VirutalObjectFactory : creating HalfScreenQuadObjects..."
						<< std::endl;

		/**
		 *  LEFT HALF SCREEN QUAD
		 */

		Mesh* quadMeshLeft = new Mesh();
		Material* quadMatLeft = new Material();

		quadMatLeft->setName("default_quad_material");
		GLuint quadVertexArrayHandleLeft;

		glGenVertexArrays(1, &quadVertexArrayHandleLeft);
		glBindVertexArray(quadVertexArrayHandleLeft);

		int indicesLeft[] = { 0, 1, 2, 3, 4, 5 };

		GLfloat positionsLeft[] = {
				-1.0f, -1.0f, 0.0f,
				0.0, -1.0f, 0.0f,
				0.0, 1.0f, 0.0f,

				0.0f, 1.0f, 0.0f,
				-1.0f, 1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f
		};

		GLfloat normalsLeft[] = {
				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,

				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0 };

		GLfloat tangentsLeft[] = {
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0,

				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0 };

		GLfloat uvCoordinatesLeft[] = {
				0.0f, 0.0f,
				0.5f, 0.0f,
				0.5f, 1.0f,

				0.5f, 1.0f,
				0.0f, 1.0f,
				0.0f, 0.0f };

		std::cout
				<< " VirutalObjectFactory : creating creating HalfScreenQuadObjects... VertexArrayObjects..."
				<< std::endl;

		GLuint indexBufferHandleLeft;
		glGenBuffers(1, &indexBufferHandleLeft);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandleLeft);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesLeft), indicesLeft,
				GL_STATIC_DRAW);

		GLuint vertexBufferHandleLeft;
		glGenBuffers(1, &vertexBufferHandleLeft);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleLeft);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positionsLeft), positionsLeft,
				GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandleLeft);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleLeft);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoordinatesLeft), uvCoordinatesLeft,
				GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandleLeft);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleLeft);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normalsLeft), normalsLeft, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandleLeft);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleLeft);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tangentsLeft), tangentsLeft,
				GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		std::cout
				<< " VirutalObjectFactory : creating HalfScreenQuadObjects... releasing buffers..."
				<< std::endl;

//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);

		std::cout
				<< " VirutalObjectFactory : creating HalfScreenQuadObjects... GraphicsComponent..."
				<< std::endl;

		quadMeshLeft->setVAO(quadVertexArrayHandleLeft);
		quadMeshLeft->setNumIndices(6);
		quadMeshLeft->setNumVertices(6);
		quadMeshLeft->setNumFaces(2);

		mHalfScreenQuadLeft = new GraphicsComponent(quadMeshLeft, quadMatLeft);

		/**
		 *  RIGHT HALF SCREEN QUAD
		 */

		Mesh* quadMeshRight = new Mesh();
		Material* quadMatRight = new Material();

		quadMatRight->setName("default_quad_material_2");
		GLuint quadVertexArrayHandleRight;

		glGenVertexArrays(1, &quadVertexArrayHandleRight);
		glBindVertexArray(quadVertexArrayHandleRight);

		int indicesRight[] = { 0, 1, 2, 3, 4, 5 };

		GLfloat positionsRight[] = {
				0.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, -1.0f,0.0f };

		GLfloat normalsRight[] = {
				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,

				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,
				0.0, 0.0, 1.0 };

		GLfloat tangentsRight[] = {
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0,

				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0,
				0.0, -1.0, 0.0 };

		GLfloat uvCoordinatesRight[] = {
				0.5f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,

				1.0f, 1.0f,
				0.5f, 1.0f,
				0.5f, 0.0f };

		std::cout
				<< " VirutalObjectFactory : creating creating HalfScreenQuadObjects... VertexArrayObjects..."
				<< std::endl;

		GLuint indexBufferHandleRight;
		glGenBuffers(1, &indexBufferHandleRight);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandleRight);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesRight),
				indicesRight, GL_STATIC_DRAW);

		GLuint vertexBufferHandleRight;
		glGenBuffers(1, &vertexBufferHandleRight);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleRight);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positionsRight), positionsRight,
				GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandleRight);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleRight);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoordinatesRight),
				uvCoordinatesRight, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandleRight);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleRight);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normalsRight), normalsRight,
				GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandleRight);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandleRight);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tangentsRight), tangentsRight,
				GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

		std::cout
				<< " VirutalObjectFactory : creating HalfScreenQuadObjects... releasing buffers..."
				<< std::endl;

//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);

		std::cout
				<< " VirutalObjectFactory : creating HalfScreenQuadObjects... GraphicsComponent..."
				<< std::endl;

		quadMeshRight->setVAO(quadVertexArrayHandleRight);
		quadMeshRight->setNumIndices(6);
		quadMeshRight->setNumVertices(6);
		quadMeshRight->setNumFaces(2);

		mHalfScreenQuadRight = new GraphicsComponent(quadMeshRight,
				quadMatRight);
	}

	if ( side == LEFT )
	{
		return mHalfScreenQuadLeft;
	}
	else
	{
		return mHalfScreenQuadRight;
	}
}

GraphicsComponent* VirtualObjectFactory::getQuad() {
	if (mQuad == 0) {

		std::cout << " VirutalObjectFactory : creating QuadObject..."
				<< std::endl;

		Mesh* quadMesh = new Mesh();
		Material* quadMat = new Material();

		quadMat->setName("default_quad_material");
		GLuint quadVertexArrayHandle;

		glGenVertexArrays(1, &quadVertexArrayHandle);
		glBindVertexArray(quadVertexArrayHandle);

		int indices[] = {0, 1, 2, 3, 4, 5};


		float size = 0.5;

	    GLfloat positions[] = {
	    	-size,-size,0.0f, size,-size,0.0f, size,size,0.0f,
        	size,size,0.0f, -size,size,0.0f, -size,-size,0.0f
	    };


	    GLfloat normals[] = {
	        0.0,  0.0,  1.0,    0.0,  0.0,  1.0,    0.0,  0.0,  1.0,
        	0.0,  0.0,  1.0,    0.0,  0.0,  1.0,    0.0,  0.0,  1.0
	    };

	    GLfloat tangents[] = {
	        0.0, -1.0,  0.0,    0.0, -1.0,  0.0,    0.0, -1.0,  0.0,
        	0.0, -1.0,  0.0,    0.0, -1.0,  0.0,    0.0, -1.0,  0.0
	    };

	    GLfloat uvCoordinates[] = {
	        0,0, 1,0, 1,1,
        	1,1, 0,1, 0,0
	    };

		std::cout
				<< " VirutalObjectFactory : creating QuadObject... VertexArrayObject..."
				<< std::endl;

		GLuint indexBufferHandle;
		glGenBuffers(1, &indexBufferHandle);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint vertexBufferHandle;
		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvCoordinates), uvCoordinates, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vertexBufferHandle);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tangents), tangents, GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		std::cout << " VirutalObjectFactory : creating QuadObject... releasing buffers..." << std::endl;

//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);

		std::cout << " VirutalObjectFactory : creating QuadObject... GraphicsComponent..." << std::endl;

		quadMesh->setVAO(quadVertexArrayHandle);
		quadMesh->setNumIndices(6);
		quadMesh->setNumVertices(6);
		quadMesh->setNumFaces(2);

		mQuad = new GraphicsComponent(quadMesh, quadMat);
	}
	return mQuad;
}

VirtualObject* VirtualObjectFactory::createNonAssimpVO(float mass) {

	if (mCube == 0) {
		NoAssimpVirtualObjectFactory *voFactory =
				new NoAssimpVirtualObjectFactory();

		mCube = voFactory->createCubeObject(mass);
	}

	return mCube;
}

VirtualObject* VirtualObjectFactory::createVirtualObject() {
	return new VirtualObject();
}

VirtualObject* VirtualObjectFactory::createVirtualObject(std::string filename,
		BodyType bodyType, float mass, int collisionFlag, bool blenderAxes) {
	VirtualObject* virtualObject = new VirtualObject();

	Assimp::Importer Importer;

	std::string directory = filename.substr(filename.find_last_of('/') + 1);
	std::string objName = directory;
	directory = filename.substr(0, filename.length() - directory.length());

	using namespace std;

	//looking up the file

	std::ifstream fin(filename.c_str());
	if (!fin.fail()) {
		fin.close();
	} else {

		cout << "Couldn't open file: " << filename.c_str() << endl;
		cout << Importer.GetErrorString() << endl;
		cout << "Have a cube instead!" << endl;

		return createNonAssimpVO();
	}

	const aiScene* pScene = Importer.ReadFile(filename,
			aiProcess_Triangulate | aiProcess_GenSmoothNormals
					| aiProcess_GenUVCoords | aiProcess_FlipUVs
					| aiProcess_ValidateDataStructure
					| aiProcess_CalcTangentSpace

					);


	
	// Melden, falls der Import nicht funktioniert hat
	if (!pScene) {
		cout << Importer.GetErrorString() << endl;
		return createNonAssimpVO();
	}

	cout << "Import of scene " << filename.c_str() << " succeeded." << endl;

	glm::mat4 inversesceneMatrix = glm::inverse(glm::transpose(glm::make_mat4x4(&(pScene->mRootNode->mTransformation.a1))));


	glm::vec3 physics_min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	glm::vec3 physics_max = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	Mesh* physMesh = new Mesh();
	btTriangleMesh* btMesh = new btTriangleMesh();
	btTriangleIndexVertexArray* btTIVA = new btTriangleIndexVertexArray();
	cout << "pScene->mNumMeshes " << pScene->mNumMeshes << endl;

	// For each mesh

//<<<<<<< HEAD
//
//	// For each mesh of the loaded object
//	for (unsigned int n = 0; n < pScene->mNumMeshes; ++n)
//	{
//		const aiMesh* mesh = pScene->mMeshes[n];
//
//        /* name of each GraphicComponent */
//        const aiString name_gc = pScene->mMeshes[n]->mName;
//        std::string str( name_gc.data, name_gc.length );
//        std::cout <<"GraphicComponent: " << str <<endl;
//
//
//		//Our Material and Mash to be filled
//=======
	for (unsigned int n = 0; n < pScene->mNumMeshes; ++n) {
		const aiMesh* mesh = pScene->mMeshes[n];

		cout << "mesh->mNumFaces " << mesh->mNumFaces << endl;


		if(pScene->mRootNode->FindNode(mesh->mName)){
			aiMatrix4x4 mesh_transform = pScene->mRootNode->FindNode(mesh->mName)->mTransformation;
				aiNode* mesh_node = pScene->mRootNode->FindNode(mesh->mName);

				while(mesh_node->mParent){
					mesh_node = mesh_node->mParent;
					mesh_transform = mesh_node->mTransformation * mesh_transform;
				}
				inversesceneMatrix = glm::make_mat4(&mesh_transform.a1);
				inversesceneMatrix = glm::transpose(inversesceneMatrix);
				inversesceneMatrix = glm::inverse(inversesceneMatrix);

//				unsigned int j = 0;
//				if(!pScene->HasAnimations())
//				for (j = 0; j < mesh->mNumVertices; ++j) {
//					//todo: fix mesh_transform
//
//					mesh->mVertices[j] = mesh_transform * mesh->mVertices[j];
//					if (mesh->HasNormals()){
//						mesh->mNormals[j] = mesh_transform.Inverse().Transpose() * mesh->mNormals[j];
//					}
//					if (mesh->HasTangentsAndBitangents()){
//						mesh->mTangents[j] = mesh_transform.Inverse().Transpose() * mesh->mTangents[j];
//					}
//				}
		}


		if (bodyType == MESH) {

			//Var A TriangleMesh; set Parameters
			btVector3 btVertex0;
			btVector3 btVertex1;
			btVector3 btVertex2;

			//Var B TriangleIndexVertexarray, set Parameters
			btIndexedMesh btIMesh; //Mesh, that gets added to TIVA
			static glm::vec3* vertexBase = new glm::vec3[mesh->mNumVertices];
			static int* triangleIndexBase = new int[mesh->mNumFaces*3];
			int y = 0; 	//index for vertexBase
			int z = 0;	//index for triangleIndexBase
			int numTriangles = 0;	//count only faces, that are triangles
			btIMesh.m_vertexStride = sizeof(float) * 3; //3*float per vertex
			btIMesh.m_triangleIndexStride = sizeof(int) *3; //3*int(3 pointer to vertices) per triangle
			btIMesh.m_numVertices = mesh->mNumVertices; //total number of vertices
			btIMesh.m_indexType = PHY_INTEGER;
			btIMesh.m_vertexType = PHY_FLOAT;

			for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {

				const aiFace& face = mesh->mFaces[i];
				/*
				*only add triangles and skip points and lines
				*assimp triangulate only breaks higher polygons into triangles
				*/
				if (face.mNumIndices == 3) {
					//Var A with TriangleMesh
					aiVector3D vec0 = mesh->mVertices[face.mIndices[0]];
					btVertex0 = btVector3(vec0.x, vec0.y, vec0.z);
					aiVector3D vec1 = mesh->mVertices[face.mIndices[1]];
					btVertex1 = btVector3(vec1.x, vec1.y, vec1.z);
					aiVector3D vec2 = mesh->mVertices[face.mIndices[2]];
					btVertex2 = btVector3(vec2.x, vec2.y, vec2.z);

					btMesh->addTriangle(btVertex0, btVertex1, btVertex2, false);


					//Var B with TriangleIndexVertexArray, set array for triangleIndexBase
					triangleIndexBase[++z] = face.mIndices[0];
					triangleIndexBase[++z] = face.mIndices[1];
					triangleIndexBase[++z] = face.mIndices[2];
					numTriangles++;
				}
			}

			//Var B, set array of vertex positions for vertexBase
			for (unsigned int k=0; k < mesh->mNumVertices; ++k){
				glm::vec3 vertex = glm::vec3(mesh->mVertices[k].x, mesh->mVertices[k].y, mesh->mVertices[k].z);
				vertexBase[++y] = vertex;
			}

			btIMesh.m_triangleIndexBase = (const unsigned char *)&triangleIndexBase[0];
			btIMesh.m_vertexBase = (const unsigned char *)&vertexBase[0].x;
			btIMesh.m_numTriangles = numTriangles;
			btTIVA->addIndexedMesh(btIMesh, PHY_INTEGER);
		}
	std::map<std::string, Bone*> bone_map;

		//Our Material and Mesh to be filled

// >>>>>>> origin/AkropolisUnderWater

		Mesh* aMesh = new Mesh();
		Material* aMat = new Material();
        
        // for Shader
        bool hasNormalMap = false;
		GraphicsComponent* gc=new GraphicsComponent(aMesh,aMat);
		vector<Bone*> bones;

		GLuint buffer = 0;
		glm::vec3 aabbMax = glm::vec3(INT_MIN, INT_MIN, INT_MIN);
		glm::vec3 aabbMin = glm::vec3(INT_MAX, INT_MAX, INT_MAX);

		//Our Indices for our Vertexlist
		std::vector<unsigned int> indices;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			unsigned int i = 0;
			for (i = 0; i < mesh->mFaces[t].mNumIndices; ++i) {
				indices.push_back(mesh->mFaces[t].mIndices[i]);
			}
		}

		unsigned int j=0;



		aMesh->setNumVertices(mesh->mNumVertices);
		aMesh->setNumIndices(mesh->mNumFaces * 3);

		// hier wurde aMesh.numFaces in dem Struct erstellt (VirtualObjectFactory.h)

		aMesh->setNumFaces(pScene->mMeshes[n]->mNumFaces);

		// generate Vertex Array for mesh
		GLuint temp = 0;
		glGenVertexArrays(1, &temp);
		aMesh->setVAO(temp);
		glBindVertexArray(aMesh->getVAO());

		// buffer for faces (indices)
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				sizeof(unsigned int) * indices.size(), &indices[0],
				GL_STATIC_DRAW);

		// buffer for vertex positions
		if (mesh->HasPositions()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER,
					sizeof(aiVector3D) * mesh->mNumVertices, mesh->mVertices,
					GL_STATIC_DRAW);

			//vertexLoc wurde hier ersetzt
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

		}

		// buffer for vertex normals
		if (mesh->HasNormals()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER,
					sizeof(float) * 3 * mesh->mNumVertices, mesh->mNormals,
					GL_STATIC_DRAW);

			// normalLoc wurde hier ersetzt
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);

		}
		if (mesh->HasTangentsAndBitangents()) {
            cout << "HAS TANGENT SPACE"<<endl;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER,
					sizeof(float) * 3 * mesh->mNumVertices, mesh->mTangents,
					GL_STATIC_DRAW);

			// normalLoc wurde hier ersetzt
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);

		}
		if(mesh->HasBones()){
			gc->setAnimated(true);
			unsigned int j;
			for (j = 0; j < mesh->mNumBones; ++j) {
				vector<float> boneweight(mesh->mNumVertices);
				aiBone *bone = mesh->mBones[j];
				unsigned int l;
				for (l = 0; l < bone->mNumWeights; ++l) {
					boneweight[bone->mWeights[l].mVertexId] = bone->mWeights[l].mWeight;
				}
				std::string name = bone->mName.C_Str();

				Bone *myBone;
				if(bone_map.find(name) != bone_map.end()){
					myBone = bone_map[name];
				}else{

					myBone = new Bone(name);


			//TODO: boners
					aiMatrix4x4 mesh_transform = bone->mOffsetMatrix;

						myBone->setInverseSceneMatrix(inversesceneMatrix );

					glm::mat4 offsetmatrix = glm::make_mat4x4(&(mesh_transform.a1));
					offsetmatrix = glm::transpose(offsetmatrix);


					myBone->setOffsetMatrix(offsetmatrix);
					bone_map.insert(std::pair<std::string, Bone*>(name, myBone));
				}
				bones.push_back(myBone);
				gc->addBone(myBone);

				glGenBuffers(1, &buffer);
				glBindBuffer(GL_ARRAY_BUFFER, buffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * boneweight.size(), &boneweight[0], GL_STATIC_DRAW);

				// normalLoc wurde hier ersetzt
				glEnableVertexAttribArray(10 + j);
				glVertexAttribPointer(10 + j, 1, GL_FLOAT, 0, 0, 0);

			}

		}

		// buffer for vertex texture coordinates
		vector<float> texCoords;
		float uv_steps = 1.0 / mesh->mNumVertices;

		if (mesh->HasTextureCoords(0)) {
			for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
				texCoords.push_back(mesh->mTextureCoords[0][k].x);
				texCoords.push_back(mesh->mTextureCoords[0][k].y);
			}
		} else {
			for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
				texCoords.push_back(k * uv_steps);
				texCoords.push_back(k * uv_steps);

			}
		}
		std::vector<glm::vec3> vertexPositions;
		for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
			if (aabbMax.x < mesh->mVertices[k].x)
				aabbMax.x = mesh->mVertices[k].x;
			if (aabbMax.y < mesh->mVertices[k].y)
				aabbMax.y = mesh->mVertices[k].y;
			if (aabbMax.z < mesh->mVertices[k].z)
				aabbMax.z = mesh->mVertices[k].z;
			if (aabbMin.x > mesh->mVertices[k].x)
				aabbMin.x = mesh->mVertices[k].x;
			if (aabbMin.y > mesh->mVertices[k].y)
				aabbMin.y = mesh->mVertices[k].y;
			if (aabbMin.z > mesh->mVertices[k].z)
				aabbMin.z = mesh->mVertices[k].z;

			vertexPositions.push_back(
					glm::vec3(mesh->mVertices[k].x, mesh->mVertices[k].y,
							mesh->mVertices[k].z));
		}
		aMesh->setVertexPosition(vertexPositions);

		// save center of mass offset matrix
		aMesh->setCenterOfMassOffsetMatrix( glm::translate( -1.0f * ( aabbMin + ( (aabbMax - aabbMin) / 2.0f ) ) ) );

		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh->mNumVertices,
				&texCoords[0], GL_STATIC_DRAW);

		//und texCoordLoc wurde dann auch ersetzt
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);

		// unbind buffers
		glBindVertexArray(0);


		// create material uniform buffer
		aiMaterial *mtl = pScene->mMaterials[mesh->mMaterialIndex];

		aiString texPath;   //contains filename of texture

		Texture *tex_temp = new Texture();

		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath)) {
			cout << "Try to find DiffuseMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setDiffuseMap(tex_temp);
		}

		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_AMBIENT, 0, &texPath)) {
			cout << "Try to find AmbientMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setAmbientMap(tex_temp);
		}

		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_OPACITY, 0, &texPath)) {
			cout << "Try to find OpacityMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setOpacityMap(tex_temp);
		}

		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_NORMALS, 0, &texPath)) {
			//For some Reason HeightMap and NormalMap are switched in Assimp
			cout << "Try to find NormalMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setNormalMap(tex_temp);
            hasNormalMap = true;
		}
		// @todo : find out whether it really is switched or not
		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_HEIGHT, 0, &texPath)) {
			//For some Reason HeightMap and NormalMap are switched in Assimp
			cout << "Try to find HeightMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setHeightMap(tex_temp);
		}

		if (AI_SUCCESS
				== mtl->GetTexture(aiTextureType_EMISSIVE, 0, &texPath)) {
			cout << "Try to find EmissiveMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setEmissiveMap(tex_temp);
		}

		if (AI_SUCCESS
				== mtl->GetTexture(aiTextureType_SPECULAR, 0, &texPath)) {
			cout << "Try to find SpecularMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setSpecularMap(tex_temp);
		}

		if (AI_SUCCESS
				== mtl->GetTexture(aiTextureType_REFLECTION, 0, &texPath)) {
			cout << "Try to find ReflectionMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setReflectionMap(tex_temp);
		}

		if (AI_SUCCESS
				== mtl->GetTexture(aiTextureType_SHININESS, 0, &texPath)) {
			cout << "Try to find ShininessMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setShininessMap(tex_temp);
		}

		if (AI_SUCCESS
				== mtl->GetTexture(aiTextureType_DISPLACEMENT, 0, &texPath)) {
			cout << "Try to find DisplacementMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setDisplacementMap(tex_temp);
		}

		if (AI_SUCCESS
				== mtl->GetTexture(aiTextureType_LIGHTMAP, 0, &texPath)) {
			cout << "Try to find LightMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setLightMap(tex_temp);
		}

		aiString name;
		if (AI_SUCCESS == aiGetMaterialString(mtl, AI_MATKEY_NAME, &name)) {
			std::string matName = name.C_Str();
			matName = matName.substr(matName.find_last_of('/') + 1);

			std::cout<<"\nName des Materials: "<<matName<<endl;

			aMat->setName(matName);
		}
		else{
			aMat->setName("genericMaterial");
		}


		/* try to generate material by name */


		MaterialManager* mm= MaterialManager::getInstance();



		if(aMat->getName().find("custom") != std::string::npos){
			cout<<"\nRead from mtl\n";



			// diffuse

			float c[4];

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

			float c[4];

			// diffuse
			set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
			aiColor4D diffuse;
			if (AI_SUCCESS
					== aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE,
							&diffuse)) {
				color4_to_float4(&diffuse, c);
			}
			aMat->setDiffuse(glm::vec3(c[0], c[1], c[2]));

			// ambient
			set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
			aiColor4D ambient;
			if (AI_SUCCESS
					== aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT,
							&ambient))
				color4_to_float4(&ambient, c);
			//memcpy(aMat.ambient, c, sizeof(c));
			aMat->setAmbient(glm::vec3(ambient.r, ambient.g, ambient.b));

			// specular

			set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);

			aiColor4D specular;
			if (AI_SUCCESS
					== aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR,
							&specular))
				color4_to_float4(&specular, c);
			//memcpy(aMat.specular, c, sizeof(c));
			aMat->setSpecular(glm::vec3(specular.r, specular.g, specular.b));

			// emission
			set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
			aiColor4D emission;
			if (AI_SUCCESS
					== aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE,
							&emission))
				color4_to_float4(&emission, c);
			//memcpy(aMat.emissive, c, sizeof(c));
			aMat->setEmission(glm::vec3(emission.r, emission.g, emission.b));

			// shininess
			float shininess = 0.0;
			//unsigned int max;
			if (AI_SUCCESS != mtl->Get(AI_MATKEY_SHININESS, shininess)){
				shininess = 50.0;

			aMat->setShininess(1.0f);
			//shininess/1000.0f
		}
	else {
			try {
				mm->makeMaterial(aMat->getName(), gc);
			} catch (string param) {
				cout << "\nFAILED: generate material by name";
			}
		}

		//Mesh und Material wird gelesen und in neuer GraphicsComponent gespeichert
		gc->setGhostObject(aabbMin, aabbMax);

        // NormalMap - check
        if (hasNormalMap == true){
            std::cout<<"NORNALMAP check"<<endl;
            gc->setNormalMap(hasNormalMap);
        }
        
		virtualObject->addGraphicsComponent(gc);

		if (aabbMin.x < physics_min.x)
			physics_min.x = aabbMin.x;
		if (aabbMin.y < physics_min.y)
			physics_min.y = aabbMin.y;
		if (aabbMin.z < physics_min.z)
			physics_min.z = aabbMin.z;
		if (aabbMax.x > physics_max.x)
			physics_max.x = aabbMax.x;
		if (aabbMax.y > physics_max.y)
			physics_max.y = aabbMax.y;
		if (aabbMax.z > physics_max.z)
			physics_max.z = aabbMax.z;

		if(pScene->HasAnimations()){
			AnimationLoop *myAnimation = makeAnimation(bone_map, pScene, true);
			virtualObject->setAnimation(myAnimation);
		}else{
			virtualObject->setAnimation(mDefaultAnimation);
		}

	}

	glm::vec3 boxValue = physics_max - physics_min;
	float width = boxValue.x;
	float height = boxValue.y;
	float depth = boxValue.z;

	float x = physics_min.x + width / 2.0f;
	float y = physics_min.y + height / 2.0f;
	float z = physics_min.z + depth / 2.0f;

	// save center of mass offset matrix
	virtualObject->setCenterOfMassOffsetMatrix( glm::translate( -x, -y, -z ) );

	glm::vec3 normal;
	normal.x = physics_min.y * physics_max.z - physics_min.z * physics_max.y;
	normal.y = physics_min.z * physics_max.x - physics_min.x * physics_max.z;
	normal.z = physics_min.x * physics_max.y - physics_min.y * physics_max.x;

	switch (bodyType) {
	case CUBE:
		virtualObject->setPhysicsComponent(width, height, depth, x, y, z, mass,
				collisionFlag);
		break;
	case PLANE:
		virtualObject->setPhysicsComponent(x, y, z, normal, mass,
				collisionFlag);
		break;
	case SPHERE:
		virtualObject->setPhysicsComponent(
				(physics_max.x - physics_min.x) / 2.0,
				(physics_max.x - physics_min.x) / 2.0 + physics_min.x,
				(physics_max.y - physics_min.y) / 2.0 + physics_min.y,
				(physics_max.z - physics_min.z) / 2.0 + physics_min.z, mass,
				collisionFlag);
		break;
	case MESH:
		virtualObject->setPhysicsComponent(x, y, z, btMesh, btTIVA);

		// ignore offset, since mesh collision shape encapsules it perfectly
		virtualObject->setCenterOfMassOffsetMatrix(glm::mat4(1.0f));

		break;
	case OTHER:
		virtualObject->setPhysicsComponent(physics_min, physics_max, mass,
				collisionFlag);
		break;
	}

	/******************************************************/
	std::cout << "BLENDER FILE ... :" << blenderAxes << std::endl;
	if (blenderAxes) {
		std::cout << "BLENDER FILE... rotating Object..." << std::endl;

		btRigidBody* rigidBody = virtualObject->getPhysicsComponent()->getRigidBody();	// rigid body object
		btMotionState* motion = rigidBody->getMotionState();							// current motion state of rigid body

		btTransform worldTrans;
		worldTrans.setIdentity();
		motion->getWorldTransform( worldTrans );			// current transformation

		btTransform blenderCorrectionTransform;				// correction : rotation
		blenderCorrectionTransform.setIdentity();

		blenderCorrectionTransform.setRotation(
				btQuaternion(btVector3(1.0f, 0.0f, 0.0f),
						((-1.0f) * PI) / 2.0f));

		btTransform newTransform;
		newTransform.setIdentity();							// transformation after correction
		newTransform.mult( blenderCorrectionTransform, worldTrans);	// apply offset then rotation

		std::cout << "BLENDER FILE... updating ModelMatrix" << std::endl;

		rigidBody->setCenterOfMassTransform(newTransform);	// set corrected transform

		virtualObject->updateModelMatrixViaPhysics();
	}
	/******************************************************/

	return virtualObject;
}


AnimationLoop* VirtualObjectFactory::makeAnimation(map<std::string, Bone*> bones, const aiScene* pScene, bool isBlender){
	AnimationLoop* myAnimation = new AnimationLoop();

	aiNode* node = pScene->mRootNode;

//	node = node->FindNode(pScene->mAnimations[0]->mChannels[0]->mNodeName);
//	node = node->mParent;

	glm::mat4 matrix = glm::transpose(glm::make_mat4(&(node->mTransformation.a1)));
	Node* myRootNode = new Node(getNodeChildren(node));
	myRootNode->setName(node->mName.C_Str());
	myRootNode->setNodeMatrix(matrix);

	unsigned int i;
	for (i = 0; i < pScene->mAnimations[0]->mNumChannels; ++i) {
		setNodeTransform(myRootNode, pScene->mAnimations[0]->mChannels[i], isBlender);
	}

	setBones(myRootNode, bones);
	//todo:solve problem, lol
	myAnimation->addNode(myRootNode);
	myAnimation->setDuration(pScene->mAnimations[0]->mDuration);

	myAnimation->updateNodes(0.0f);

	return myAnimation;
}

vector<Node*> VirtualObjectFactory::getNodeChildren(aiNode* node){
	vector<Node*> children;

	unsigned int i;
	for (i = 0; i < node->mNumChildren ; ++i) {
		Node* temp = new Node(getNodeChildren(node->mChildren[i]));
		temp->setName(node->mChildren[i]->mName.C_Str());
		glm::mat4 matrix = glm::transpose(glm::make_mat4(&(node->mTransformation.a1)));

		temp->setNodeMatrix(matrix);
		children.push_back(temp);
	}
	return children;
}

void VirtualObjectFactory::setNodeTransform(Node* node, aiNodeAnim* nodeanim, bool isBlender){
	std::string name = nodeanim->mNodeName.C_Str();

	unsigned int i;

	if(name == node->getName()){
		for (i = 0; i < nodeanim->mNumPositionKeys; ++i) {
			float time = nodeanim->mPositionKeys[i].mTime;

			glm::vec3 position = glm::vec3(nodeanim->mPositionKeys[i].mValue.x, nodeanim->mPositionKeys[i].mValue.y, nodeanim->mPositionKeys[i].mValue.z);
			glm::vec3 scale = glm::vec3(nodeanim->mScalingKeys[i].mValue.x, nodeanim->mScalingKeys[i].mValue.y, nodeanim->mScalingKeys[i].mValue.z);
			glm::quat rotation = glm::quat(nodeanim->mRotationKeys[i].mValue.w, nodeanim->mRotationKeys[i].mValue.x, nodeanim->mRotationKeys[i].mValue.y, nodeanim->mRotationKeys[i].mValue.z);
//			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

			aiQuaternion quat = nodeanim->mRotationKeys[i].mValue;

//			glm::vec3 axis = glm::vec3(glm::asin(quat.x), glm::asin(quat.y), glm::asin(quat.z));
//			float angle = glm::acos(quat.w);
//
//			glm::mat4 rot = glm::rotate(glm::mat4(), glm::degrees(angle), axis);

//			rotation = glm::quat_cast(rot);

			node->addTransformation(position, scale, glm::normalize(rotation), time);
		}
	}

	for (i = 0; i < node->getChildren().size(); ++i) {
		setNodeTransform(node->getChildren()[i], nodeanim, isBlender);
	}
}

void VirtualObjectFactory::setBones(Node* node, map<std::string, Bone*> bones){

	if(bones.find(node->getName()) != bones.end()){
		node->setBone(bones[node->getName()]);
	}else{
		node->setBone(mDefaultBone);
	}

	unsigned int i;
	for (i = 0; i < node->getChildren().size(); ++i) {
		setBones(node->getChildren()[i], bones);
	}
}
