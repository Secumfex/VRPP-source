/*
 * VirtualObjectFactory.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/VirtualObjectFactory.h>


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

VirtualObject* VirtualObjectFactory::createCow(){

	if(mCow == NULL)
		mCow = createVirtualObject(RESOURCES_PATH "/cow.obj");

	return mCow;
}


VirtualObject* VirtualObjectFactory::createVirtualObject(){
	return new VirtualObject();
}



VirtualObject* VirtualObjectFactory::createVirtualObject(std::string filename){
	VirtualObject* virtualObject = new VirtualObject();
	
	    Assimp::Importer Importer;

	//looking up the file
    std::ifstream fin(filename.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{

       cout<<"Couldn't open file: " << filename.c_str()<<endl;
       cout<<Importer.GetErrorString()<<endl;
       cout<<"Have a cow instead!"<<endl;

       return createCow();
    }
 
   const aiScene* pScene = Importer.ReadFile( filename,
		   aiProcess_Triangulate |
		   aiProcess_GenSmoothNormals|
		   aiProcess_GenUVCoords |
		   aiProcess_FlipUVs|
		   aiProcess_FlipUVs |
		   aiProcess_PreTransformVertices
		   );
 
    // Melden, falls der Import nicht funktioniert hat
    if( !pScene)
    {
        cout<<Importer.GetErrorString()<<endl;

        return createCow();


    }
 
    cout<<"Import of scene " <<filename.c_str()<<" succeeded."<<endl;


 /*  für später evtl drin lassen?!


    aiVector3D scene_min, scene_max, scene_center;
    get_bounding_box(&scene_min, &scene_max);
    float tmp;
    tmp = scene_max.x-scene_min.x;
    tmp = scene_max.y - scene_min.y > tmp?scene_max.y - scene_min.y:tmp;
    tmp = scene_max.z - scene_min.z > tmp?scene_max.z - scene_min.z:tmp;
    scaleFactor = 1.f / tmp;
 */


	// assimp Mesh mit Materialien wird erstellt und befuellt



	 // struct MyMesh aMesh;




 
    // For each mesh
    for (unsigned int n = 0; n < pScene->mNumMeshes; ++n)
    {
        const aiMesh* mesh = pScene->mMeshes[n];

        //Our Material and Mash to be filled
        Mesh* aMesh=new Mesh();
        Material* aMat=new Material();
 
        GLuint buffer = 0;
        unsigned int *faceArray;

        //Our Indices for our Vertexlist
        vector<unsigned int> indices;

        faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
        unsigned int faceIndex = 0;
 
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            unsigned int i=0;
            for (i = 0; i < mesh->mFaces[t].mNumIndices; ++i) {
            	indices.push_back(mesh->mFaces[t].mIndices[i]);
			}
        }

        aMesh->setNumVertices(mesh->mNumVertices);
        aMesh->setNumIndices(mesh->mNumFaces * 3);


		// hier wurde aMesh.numFaces in dem Struct erstellt (VirtualObjectFactory.h)
        aMesh->setNumFaces(pScene->mMeshes[n]->mNumFaces);
 
        // generate Vertex Array for mesh
		GLuint temp = 0;
		glGenVertexArrays(1,&temp);
		glBindVertexArray(aMesh->getVAO());
		aMesh->setVAO(temp);

		cout<< buffer << " buffer" << endl;

        // buffer for faces
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, &indices[0], GL_STATIC_DRAW);

        cout<< buffer << " buffer" << endl;

        // buffer for vertex positions
        if (mesh->HasPositions()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);

			//vertexLoc wurde hier ersetzt
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
            cout<< buffer << " buffer" << endl;
        }

        // buffer for vertex normals
        if (mesh->HasNormals()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
            // normalLoc wurde hier ersetzt
			glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);
            cout<< buffer << " buffer" << endl;
        }

        // buffer for vertex texture coordinates
        if (mesh->HasTextureCoords(0)) {
            float *texCoords = (float *)malloc(sizeof(float)*2*mesh->mNumVertices);
            for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
 
                texCoords[k*2]   = mesh->mTextureCoords[0][k].x;
                texCoords[k*2+1] = mesh->mTextureCoords[0][k].y;
 
            }
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
            //und texCoordLoc wurde dann auch ersetzt
			glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);
            cout<< buffer << " buffer" << endl;
        }
 

        // unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
 
        // create material uniform buffer
        aiMaterial *mtl = pScene->mMaterials[mesh->mMaterialIndex];
 
        aiString texPath;   //contains filename of texture
        if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath)){
                //bind texture
                unsigned int texId = textureIdMap[texPath.data];
                aMesh->setTexIndex(texId);
                aMat->texCount = 1;
            }
        else
            aMat->texCount = 0;



        float c[4];
        set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            color4_to_float4(&diffuse, c);
        
		
		//memcpy(aMat.diffuse, c, sizeof(c));
		aMat->setDiffuse(glm::vec4(diffuse.r,diffuse.g, diffuse.b, diffuse.a));


        set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
        aiColor4D ambient;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
            color4_to_float4(&ambient, c);


        //memcpy(aMat.ambient, c, sizeof(c));
		aMat->setAmbient(glm::vec4(ambient.r, ambient.g, ambient.b, ambient.a));



        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D specular;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
            color4_to_float4(&specular, c);


        //memcpy(aMat.specular, c, sizeof(c));
		aMat->setSpecular(glm::vec4(specular.r, specular.g, specular.b, specular.a));



        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D emission;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
            color4_to_float4(&emission, c);
       
		
		
		//memcpy(aMat.emissive, c, sizeof(c));
		aMat->setEmission(glm::vec4(emission.r, emission.g, emission.b, emission.a));




        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        aMat->setShininess(shininess);
 
		//Mesh und Material wird gelesen und in neuer GraphicsComponent gespeichert
		GraphicsComponent* gc=new GraphicsComponent(aMesh, aMat);


		virtualObject->addGraphicsComponent(gc);



    }

	
	return virtualObject;
}





VirtualObject* VirtualObjectFactory::createVirtualObject(vector<GraphicsComponent*> graphcomps){
	VirtualObject* virtualObject = new VirtualObject();
	//TODO: alle GraphicsComponents werden an das VO übergeben

	return virtualObject;
}




VirtualObject* VirtualObjectFactory::copyVirtualObject(VirtualObject vo){
	VirtualObject* virtualObject = new VirtualObject();
	//TODO: variable wird überfuehrt

	return virtualObject;
}
