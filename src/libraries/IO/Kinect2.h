#pragma once


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

#include "Visuals/RenderManager.h"
#include "Visuals/Shader.h"
#include "IO/SelectionHandler.h"
#include "IO/PlayerCamera.h"




#include <Windows.h>
#include <Ole2.h>

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>

#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>



class Kinect
{
public:
	//GLuint* textureId;              // ID of the texture to contain Kinect RGB Data
//GLubyte* datap[640*480*4];  // BGRA array containing the texture data
GLubyte data[640*480*4];



// Kinect variables
HANDLE depthStream;              // The identifier of the Kinect's RGB Camera
INuiSensor* sensor;            // The kinect sensor

bool isnew;
float* force;
float forceDirection;


float* forceOldp;
float* forceNewp;
float forceOld;
float forceNew;

	bool initKinect();

	float getKinectData(GLubyte* dest);

	Kinect(void);
	
	~Kinect(void);
};

