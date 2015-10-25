#pragma once

#include "gameobject.h"


class DynamicObject : public GameObject{

private:
    GLboolean _solidOrWire;
protected:
	Vector3 _speed;
    GLdouble _vel;
    GLdouble _angle;
    GLfloat _hitboxRadius;
public:
	DynamicObject();
	~DynamicObject();
	GLvoid update(GLdouble delta_t);
	GLvoid setSpeed(Vector3 &speed);
	GLvoid setSpeed(GLdouble x, GLdouble y, GLdouble z);
    GLboolean getSolidOrWire();
    GLvoid changeSolidOrWire();
	Vector3 getSpeed();
    GLfloat getHitboxRadius();
    GLvoid setVel(GLdouble vel);
    GLvoid setAngle(GLdouble angle);
    GLdouble getVel();
    GLdouble getAngle();
};