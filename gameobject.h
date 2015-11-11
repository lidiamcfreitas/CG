#pragma once

#include "definitions.h"
#include "vector3.h"
#include <vector>


class GameObject{

private:
    Vector3 _position;
    
public:
	GameObject();
	~GameObject();
	virtual GLvoid draw();
	virtual GLvoid update(GLdouble delta_t);
    Vector3 getPosition();
    GLdouble getPositionX();
    GLdouble getPositionY();
    GLdouble getPositionZ();
    Vector3 setPosition(GLdouble x, GLdouble y, GLdouble z);
    Vector3 setPosition(Vector3 &p);
    GLvoid material(GLfloat amb[], GLfloat diff[], GLfloat spec[], GLfloat shine);
};

