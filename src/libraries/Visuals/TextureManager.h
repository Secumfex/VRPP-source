/*
 * TextureManager.h
 *
 *  Created on: 17.12.2013
 *      Author: Raphimulator
 */

#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <Tools/TextureTools.h>
#include <Patterns/Singleton.h>

using namespace std;

class TextureManager : public Singleton<TextureManager>{
public:
	friend class Singleton<TextureManager>;
	/** \brief default constructor
	 *
	 */
	TextureManager();

	/** \brief destructor
	 *
	 */
	virtual ~TextureManager();

	/** \brief creates a Texture and inserts a texture handle into a map
	 *
	 * @param filename
	 */
	bool createTextureHandle(string filename);

	/** \brief getter
	 *
	 * @return the desired Texture by its name
	 */
	GLuint getTextureHandle(string filename);

protected:
	map<string, GLuint> mTextureHandles;	/**< !docu pls! */

};

#endif /* TEXTUREMANAGER_H_ */
