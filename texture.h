//
//  texture.h
//  cg_code
//
//

#ifndef texture_h
#define texture_h

#include <stdio.h>
#include "SOIL.h"
#include "gameobject.h"

class Texture :public GameObject {
private:
    GLint _texture;
    bool _defTex;
    std::string _image;
public:
    Texture(void);
    ~Texture(void);
    
    Texture(const char* name);
    const char* getImage(){ return _image.c_str(); }
    void setImage(const char* a){ _image = a; }
    void setTexture(GLuint a){ _texture = a; }
    GLuint getTexture(){ return _texture; }
    GLboolean loadTexture(GLint index);
    void draw();
    
};

#endif /* texture_h */
