#ifndef texture_h
#define texture_h

#include "definitions.h"
#include "SOIL.h"

class Texture {
private:
    GLuint _texture;

public:
    Texture();
    ~Texture();
	GLboolean loadTexture(char* fileName);
	GLuint getTexture();
    
};

#endif /* texture_h */
