#ifndef pointlight_hpp
#define pointlight_hpp

#include "DynamicObject.h"
#include "vector4.h"

class Pointlight: public DynamicObject{

private:
    Vector4 _mat_emiss;

public:
    Pointlight(GLdouble x, GLdouble y, GLdouble z);
    ~Pointlight();
    GLvoid draw();
    GLfloat getEmissionX();
    GLvoid setMatEmission(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
};

#endif
