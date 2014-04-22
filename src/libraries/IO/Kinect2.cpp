#include "Kinect2.h"
	#define width 640
#define height 480



//  http://www.cs.princeton.edu/~edwardz/tutorials/kinect/kinect2.html  
//initKinect & getKinectData are taken from the tutorial  but are edited by me
bool Kinect::initKinect() {
    // Get a working kinect sensor
    int numSensors;
    if (NuiGetSensorCount(&numSensors) < 0 || numSensors < 1) return false;
    if (NuiCreateSensorByIndex(0, &sensor) < 0) return false;

    // Initialize sensor
    sensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH);
    sensor->NuiImageStreamOpen(
        NUI_IMAGE_TYPE_DEPTH,            // Depth camera or rgb camera?
        NUI_IMAGE_RESOLUTION_640x480,    // Image resolution
        0,      // Image stream flags, e.g. near mode
        2,      // Number of frames to buffer
        NULL,   // Event handle
        &depthStream);
    return sensor;
}



float Kinect::getKinectData(GLubyte* dest) {
    NUI_IMAGE_FRAME imageFrame;
    NUI_LOCKED_RECT LockedRect;
    if (sensor->NuiImageStreamGetNextFrame(depthStream, 0, &imageFrame) < 0) return 0;
    INuiFrameTexture* texture = imageFrame.pFrameTexture;
    texture->LockRect(0, &LockedRect, NULL, 0);

	if (LockedRect.Pitch != 0)
    {
            const USHORT* curr = (const USHORT*) LockedRect.pBits;
        const USHORT* dataEnd = curr + (width*height);

        while (curr < dataEnd) {
            // Get depth in millimeters
            USHORT depth = NuiDepthPixelToDepth(*curr++);
            // Draw a grayscale image of the depth:
            // B,G,R are all set to depth%256, alpha set to 1.
            for (int i = 0; i < 3; ++i){
                *dest++ = (BYTE) depth%256;			
			}
            *dest++ = 0xff;
        }
    }
    texture->UnlockRect(0);
    sensor->NuiImageStreamReleaseFrame(depthStream, &imageFrame);

	//this is from me from here on
	float temp=0;
	for(int i=0; i<640*480*4; i+=16){
	temp+=data[i];
	}
	
	return temp/100000 ;
}



Kinect::Kinect(void)
{
	force=&forceDirection;
	forceOldp=&forceOld;
	forceNewp=&forceNew;
	isnew=false;
	forceOld=0;
	forceNew=0;
}


Kinect::~Kinect(void)
{
}