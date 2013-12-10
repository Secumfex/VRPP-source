/*
 * VirtualObjectFactory.cpp
 *
 *  Created on: 05.12.2013
 *      Author: Raphimulator
 */

#include <Visuals/VirtualObjectFactory.h>


//eingefügt
void set_float4(float f[4], float a, float b, float c, float d)
{
f[0] = a;
f[1] = b;
f[2] = c;
f[3] = d;
}
 
void color4_to_float4(const aiColor4D *c, float f[4])
{
f[0] = c->r;
f[1] = c->g;
f[2] = c->b;
f[3] = c->a;
}



VirtualObject* VirtualObjectFactory::createVirtualObject(){
	return new VirtualObject();
}
VirtualObject* VirtualObjectFactory::createVirtualObject(std::string filename){
	VirtualObject* virtualObject = new VirtualObject();
	
	    Assimp::Importer Importer;


	
	//TODO: filename wird im System gefunden



	//gucken, ob file existiert
    std::ifstream fin(filename.c_str());
    if(!fin.fail()) {
        fin.close();
    }
    else{
        printf("Couldn't open file: %s\n", filename.c_str());
        printf("%s\n", Importer.GetErrorString());
        return false;
    }
 
   const aiScene* pScene = Importer.ReadFile( filename, aiProcessPreset_TargetRealtime_Quality|aiProcess_Triangulate | aiProcess_GenSmoothNormals);
 
    // Melden, falls der Import nicht funktioniert hat
    if( !pScene)
    {
        printf("%s\n", Importer.GetErrorString());
        
		// richtig so?  bzw. was ausgeben bei misserfolg?
		return false;


    }
 
    // Erfolg berichten. Jetzt können wir mit dem import arbeiten
    printf("Import of scene %s succeeded.",filename.c_str());


 /*  für später evtl drin lassen?!


    aiVector3D scene_min, scene_max, scene_center;
    get_bounding_box(&scene_min, &scene_max);
    float tmp;
    tmp = scene_max.x-scene_min.x;
    tmp = scene_max.y - scene_min.y > tmp?scene_max.y - scene_min.y:tmp;
    tmp = scene_max.z - scene_min.z > tmp?scene_max.z - scene_min.z:tmp;
    scaleFactor = 1.f / tmp;
 */


	//TODO: assimp Mesh mit Materialien wird erstellt und befuellt



	  struct MyMesh aMesh;
    struct MyMaterial aMat;
    GLuint buffer;
 
    // For each mesh
    for (unsigned int n = 0; n < pScene->mNumMeshes; ++n)
    {
        const aiMesh* mesh = pScene->mMeshes[n];
 
        // create array with faces
        // have to convert from Assimp format to array

		//kein array?!
        unsigned int *faceArray;


        faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
        unsigned int faceIndex = 0;
 
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
            const aiFace* face = &mesh->mFaces[t];
 
            memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
            faceIndex += 3;
        }

		// hier wurde aMesh.numFaces in dem Struct erstellt (VirtualObjectFactory.h)
        aMesh.numFaces = pScene->mMeshes[n]->mNumFaces;
 
        // generate Vertex Array for mesh
        glGenVertexArrays(1,&(aMesh.vao));
        glBindVertexArray(aMesh.vao);
 
        // buffer for faces
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
 
        // buffer for vertex positions
        if (mesh->HasPositions()) {
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);

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
			glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, 0);
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
			glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, 0, 0, 0);
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
                aMesh.texIndex = texId;
                aMat.texCount = 1;
            }
        else
            aMat.texCount = 0;



        float c[4];
        set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
        aiColor4D diffuse;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
            color4_to_float4(&diffuse, c);
        memcpy(aMat.diffuse, c, sizeof(c));
 
        set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
        aiColor4D ambient;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
            color4_to_float4(&ambient, c);
        memcpy(aMat.ambient, c, sizeof(c));
 
        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D specular;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
            color4_to_float4(&specular, c);
        memcpy(aMat.specular, c, sizeof(c));
 
        set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
        aiColor4D emission;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
            color4_to_float4(&emission, c);
        memcpy(aMat.emissive, c, sizeof(c));
 
        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        aMat.shininess = shininess;
 
        glGenBuffers(1,&(aMesh.uniformBlockIndex));
        glBindBuffer(GL_UNIFORM_BUFFER,aMesh.uniformBlockIndex);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(aMat), (void *)(&aMat), GL_STATIC_DRAW);
 
		// der vector wurde jetzt in VirtualObjectFactory.h static(!) erstellt. ist das in ordnung?
        myMeshes.push_back(aMesh);
    }


	//TODO: Mesh und Material wird gelesen und in neuer GraphicsComponent gespeichert
	//TODO: SPÄTER: Wenn moeglich mehr als eine GraphicComponente aus einem Mesh lesen
	//TODO: GraphicsComponent(s) and virtualOBject.addGraphicComponent weitergeben.
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
