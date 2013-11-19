#include "Resource.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <GLFW/glfw3.h>


//---------------RESOURCE SCOPE--------------------

void Resource :: setName(char* name){
	mName = name;

}


//---------------TEXTURE SCOPE--------------------

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(mNormals), mNormals, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(mUVs), mUVs, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
//

}

void Mesh :: getResource(const char* filename){
    
    ifstream in(filename, ios::in);
    if (!in)
    {
        cerr << "Objekt kann nicht geoeffnet werden..." << filename << endl;
        exit(1);
        
    }
    cout << "Objekt geoeffnet..." << filename << endl;
    std::string line;
    while (std::getline(in, line))
    {
        //cout<<line<<endl;
        if (line.substr(0,2)=="v "){
            std::istringstream v(line.substr(2));
            glm::vec3 vert;
            double x,y,z;
            v>>x;v>>y;v>>z;
            vert=glm::vec3(x,y,z);
            mVertices.push_back(vert);
        }
        else if(line.substr(0,2)=="f "){
            std::istringstream v(line.substr(2));
            GLuint a,b,c;
            v>>a;v>>b;v>>c;
            a--;b--;c--;
            mIndices.push_back(a);
            mIndices.push_back(b);
            mIndices.push_back(c);
        }
        
    }
    for(unsigned int i=0;i<mIndices.size();i++)
    {
        glm::vec3 meshData;
        meshData=glm::vec3(mVertices[mIndices[i]].x,mVertices[mIndices[i]].y,mVertices[mIndices[i]].z);
        meshVertices.push_back(meshData);
        
    }
}

vector<glm::vec3> Mesh::returnMesh()
{
    return meshVertices;
}
    
	//TODO: GLMModel machen

	//TODO: file finden und das Model damit füttern

	//TODO: Alle notwendigen Daten aus dem Model lesen

	//TODO: Model löschen



