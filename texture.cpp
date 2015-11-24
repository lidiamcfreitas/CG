//
//  texture.cpp
//  cg_code
//
//

#include "texture.h"

Texture::Texture(){}

Texture::~Texture(){}

GLboolean Texture::loadTexture(char* fileName) {
    
      _texture = SOIL_load_OGL_texture(
                    fileName,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
                    );
    if(_texture == 0)
        return false;
	    
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    return true;                                        // Return Success
}

GLuint Texture::getTexture(){
	return _texture;
}