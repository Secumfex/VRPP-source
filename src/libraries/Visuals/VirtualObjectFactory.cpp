/*

 * VirtualObjectFactory.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/VirtualObjectFactory.h>
#include <string>

VirtualObjectFactory::VirtualObjectFactory(){
	mCube = NULL;
	mScreenFillTriangle = NULL;
	mDefaultBone = new Bone();
	mDefaultAnimation = new AnimationLoop();
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

VirtualObject* VirtualObjectFactory::createNonAssimpVO(float mass){

	if(mCube == NULL){
		NoAssimpVirtualObjectFactory *voFactory = new NoAssimpVirtualObjectFactory();
		mCube = voFactory->createCubeObject(mass);
	}

	return mCube;
}


bool VirtualObjectFactory::checkIfBlender(std::string filename){
	std::ifstream myfile(filename.c_str());
	if(myfile.fail())
		return false;
	if (myfile.is_open())
	{
		std::string line;

		if(filename.find("dae") != std::string::npos)
			for (string line; getline(myfile, line);) {
				//			std::cout << line << std::endl;
				if(line.find("Blender") != std::string::npos || line.find("blender") != std::string::npos){
					std::cout << "Looks like this is a blender file." << std::endl;
					return true;
				}
			}
	}
	return false;
}


void VirtualObjectFactory::fixBlenderMatrix(glm::mat4 &matrix){
	matrix = glm::rotate(matrix, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

VirtualObject* VirtualObjectFactory::createVirtualObject(){
	return new VirtualObject();
}

VirtualObject* VirtualObjectFactory::createVirtualObject(std::string filename, BodyType bodyType, float mass){

	VirtualObject* virtualObject = new VirtualObject();

	Assimp::Importer Importer;

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

	//todo: scenen transformation bla

	glm::mat4 inversesceneMatrix = glm::inverse(glm::transpose(glm::make_mat4x4(&(pScene->mRootNode->mTransformation.a1))));

	// Melden, falls der Import nicht funktioniert hat
	if( !pScene)
	{
		cout<<Importer.GetErrorString()<<endl;
		return createNonAssimpVO();
	}
	cout<<"Import of scene " <<filename.c_str()<<" succeeded."<<endl;

	bool isBlender = checkIfBlender(filename);

	glm::vec3 physics_min = glm::vec3(FLT_MAX,FLT_MAX,FLT_MAX);
	glm::vec3 physics_max = glm::vec3(-FLT_MAX,-FLT_MAX,-FLT_MAX);

	std::map<std::string, Bone*> bone_map;

	// For each mesh of the loaded object
	for (unsigned int n = 0; n < pScene->mNumMeshes; ++n)
	{
		const aiMesh* mesh = pScene->mMeshes[n];


		//Our Material and Mash to be filled
		Mesh* aMesh = new Mesh();
		Material* aMat = new Material();
		GraphicsComponent* gc=new GraphicsComponent(aMesh,aMat);
		vector<Bone*> bones;

		GLuint buffer = 0;
		glm::vec3 aabbMax = glm::vec3(INT_MIN, INT_MIN, INT_MIN);
		glm::vec3 aabbMin = glm::vec3(INT_MAX, INT_MAX, INT_MAX);


		//Our Indices for our Vertexlist
		vector<unsigned int> indices;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			unsigned int i=0;
			for (i = 0; i < mesh->mFaces[t].mNumIndices; ++i) {
				indices.push_back(mesh->mFaces[t].mIndices[i]);
			}
		}

		unsigned int j=0;


		if(pScene->mRootNode->FindNode(mesh->mName))
				for (j = 0; j < mesh->mNumVertices; ++j) {
					//todo: fix mesh_transform
					glm::mat4 blamatrix = glm::transpose(glm::make_mat4(&(pScene->mRootNode->FindNode(mesh->mName)->mTransformation.a1)));

					mesh->mVertices[j] = pScene->mRootNode->FindNode(mesh->mName)->mTransformation * mesh->mVertices[j];
					if(!pScene->HasAnimations())
					mesh->mVertices[j] = pScene->mRootNode->mTransformation * mesh->mVertices[j];
					if (mesh->HasNormals()){
						if(!pScene->HasAnimations())
						mesh->mNormals[j].Set(mesh->mNormals[j].x, mesh->mNormals[j].z, -mesh->mNormals[j].y);
					}
					if (mesh->HasTangentsAndBitangents()){
						if(!pScene->HasAnimations())
						mesh->mTangents[j].Set(mesh->mTangents[j].x, mesh->mTangents[j].z, -mesh->mTangents[j].y);
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
			//TODO: boners
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
					aiVector3t<float> scale;
					aiQuaterniont<float> rotate;
					aiVector3t<float> translate;
					bone->mOffsetMatrix.Decompose(scale, rotate, translate);

					glm::mat4 modelmatrix = glm::transpose(glm::make_mat4(&(pScene->mRootNode->FindNode(mesh->mName)->mTransformation.a1)));
					cout << "THIS IS MODELMATRIX " << glm::to_string(modelmatrix) << endl;

						myBone->setInverseSceneMatrix(inversesceneMatrix );

					glm::mat4 offsetmatrix = glm::make_mat4x4(&(bone->mOffsetMatrix.a1));
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
		vector <float>texCoords;
		float uv_steps = 1.0 / mesh->mNumVertices;

		if (mesh->HasTextureCoords(0))
			for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
				texCoords.push_back(mesh->mTextureCoords[0][k].x);
				texCoords.push_back(mesh->mTextureCoords[0][k].y);
			}else
				for(unsigned int k = 0; k < mesh->mNumVertices; ++k){
					texCoords.push_back(k * uv_steps);
					texCoords.push_back(k * uv_steps);

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

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_HEIGHT, 0, &texPath)){
			//For some Reason HeightMap and NormalMap are switched in Assimp
			cout << "Try to find NormalMap: " << texPath.C_Str() << endl;
			tex_temp = new Texture(directory + texPath.C_Str());
			aMat->setNormalMap(tex_temp);
		}

		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_NORMALS, 0, &texPath)){
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

		std::cout << "max: " << physics_max.x << " , "<< physics_max.y << " , "<< physics_max.z << std::endl;
		std::cout << "min: " << physics_min.x << " , "<< physics_min.y << " , "<< physics_min.z << std::endl;

	}


	if(pScene->HasAnimations()){
		AnimationLoop *myAnimation = makeAnimation(bone_map, pScene, isBlender);
		virtualObject->setAnimation(myAnimation);
	}else{
		virtualObject->setAnimation(mDefaultAnimation);
	}

	glm::vec3 normal=physics_max;

	switch(bodyType){
	case CUBE:		virtualObject->setPhysicsComponent(physics_max.x-physics_min.x, physics_max.y-physics_min.y, physics_max.z-physics_min.z, physics_max.x, physics_max.y, physics_max.z, mass);
	break;
	case PLANE:		virtualObject->setPhysicComponent(physics_min.x,physics_min.y,physics_min.z,normal,mass);
	break;
	case SPHERE:	virtualObject->setPhysicsComponent(physics_max.x-physics_min.x, (physics_max.x-physics_min.x)/2.0+physics_min.x, (physics_max.y-physics_min.y)/2.0+physics_min.y, (physics_max.z-physics_min.z)/2.0+physics_min.z, mass);
	break;
	case OTHER:		virtualObject->setPhysicsComponent(physics_min, physics_max, mass);
	break;
	}


	return virtualObject;
}


AnimationLoop* VirtualObjectFactory::makeAnimation(map<std::string, Bone*> bones, const aiScene* pScene, bool isBlender){
	AnimationLoop* myAnimation = new AnimationLoop();

	aiNode* node = pScene->mRootNode;
	cout <<  node->mName.C_Str() << " name of root"<< endl;


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

	for (std::map<std::string, Bone*> ::iterator it=bones.begin(); it!=bones.end(); ++it) {
	Bone* tempBone = it->second;
	getBoneTransform(node->FindNode(tempBone->getName().c_str()));
	cout << glm::to_string(	tempBone->getInverseMatrix() * tempBone->getOffsetMatrix()) << endl;
	}

	setBones(myRootNode, bones);
	//todo:solve problem, lol
	myAnimation->addNode(myRootNode);
	myAnimation->setDuration(pScene->mAnimations[0]->mDuration);
//	myAnimation->setStartTransformation(armaturematrix);

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

			glm::mat4 transform = glm::mat4_cast(rotation) * glm::translate(glm::mat4(1.0f), position)  * glm::scale(glm::mat4(1.0f), scale);

			node->addTransformation(position, scale, rotation, time);
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

glm::mat4 VirtualObjectFactory::getBoneTransform(aiNode* node){

		std::cout << "WHAT" << node->mName.C_Str() << std::endl;
		aiMatrix4x4 mat ;
		while(node->mParent){
			mat = node->mTransformation * mat;
			node = node->mParent;
		}
			mat = node->mTransformation * mat;

			glm::mat4 matrix = glm::transpose(glm::make_mat4(&(mat.a1)));
		cout << node->mName.C_Str() <<" " << glm::to_string(matrix) << endl;

	return glm::mat4();
}

