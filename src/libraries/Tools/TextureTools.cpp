#include <iostream>
#include "stb_image.h"
#include "TextureTools.h"

namespace TextureTools {
    GLuint loadTexture(std::string fileName){
        int width, height, bytesPerPixel;
        unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &bytesPerPixel, 0);

        if(data == NULL){
        	std::cout << "ERROR: Unable to open image "  << fileName << std::endl;
        	  return -1;}

        //create new texture
        GLuint textureHandle;
        glGenTextures(1, &textureHandle);
     
        //bind the texture
        glBindTexture(GL_TEXTURE_2D, textureHandle);
     
        //send image data to the new texture
        if (bytesPerPixel < 3) {
        	std::cout << "ERROR: bytes per pixel are to low : " << bytesPerPixel << std::endl;
            std::cout << "ERROR: Unable to open image"  << fileName << std::endl;
            return -1;
        } else if (bytesPerPixel == 3){

        	// to ensure textures with odd dimensions can be buffered
        	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

        	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (bytesPerPixel == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "WARNING: Unknown format for bytes per pixel... Changed to \"4\"" << std::endl;
            glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }

        //texture settings
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, true);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        std::cout << "SUCCESS: image loaded from " << fileName << std::endl;
        return textureHandle;
    }
}
