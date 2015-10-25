#pragma once
#include "dynamicobject.h"

class Car : public DynamicObject{
private:
    GLboolean _up;
    GLboolean _down;
    GLboolean _right;
    GLboolean _left;
    Vector3 _previous_position;
public:
	Car();
	~Car();
	virtual GLvoid draw();
    virtual GLvoid drawWheel(GLfloat wheelx, GLfloat wheely, GLfloat wheelz, GLfloat wheelInner, GLfloat wheelOuter, GLboolean sw);
    GLvoid update(GLdouble delta_t);
    GLboolean getKeyUp();
    GLboolean getKeyDown();
    GLboolean getKeyRight();
    GLboolean getKeyLeft();
    GLvoid setKeyUp(GLboolean value);
    GLvoid setKeyDown(GLboolean value);
    GLvoid setKeyRight(GLboolean value);
    GLvoid setKeyLeft(GLboolean value);
    GLvoid crash();
    GLvoid reset();
};
