//
//  texture.cpp
//  cg_code
//
//

#include "texture.h"

Texture::Texture()
{
    
}

Texture::Texture(const char* name)
{
    setImage(name);
    _defTex = true;
}


Texture::~Texture(void)
{
}

GLboolean Texture::loadTexture(GLint index) {
    
      _texture[index] = SOIL_load_OGL_texture(
                    "ground.png",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y
                    );
    if(_texture[index] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, _texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    return true;                                        // Return Success
}