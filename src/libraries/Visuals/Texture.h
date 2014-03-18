/*
 * Texture.h
 *
 *  Created on: 06.12.2013
 *      Author: Raphimulator
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <Visuals/TextureManager.h>
#include <string>



class Texture {
	//-----------------MEMBER FUNCTIONS-----------------
public:
	/** Man macht die Textur direkt mit dem Dateinamen */

	/** \brief constructor
	 *
	 * @param filename
	 */
	Texture(std::string filename);

	/** \brief default constructor
	 *
	 */
	Texture();

	/** \brief destructor
	 *
	 */
	virtual ~Texture();

	/** \brief getter
	 *
	 * @return mFilename
	 */
	std::string getTexName();

	/** \brief getter
	 *
	 * @return the Texture's handle
	 */
	GLuint getTextureHandle();

	/** \brief binds Texture
	 *
	 */
	void bindTexture();

	/** \brief unbinds Texture
	 *
	 */
	void unbindTexture();

	//-----------------MEMBER VARIABLES-----------------
protected:

	string mFilename;				/**< !docu pls! */

	TextureManager* mTexManager;	/**< !docu pls! */
};

#endif /* TEXTURE_H_ */
