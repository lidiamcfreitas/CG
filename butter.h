#pragma once
#include "dynamicobject.h"


class Butter : public DynamicObject{
private:
    GLfloat _angle;
public:
	Butter();
	~Butter();
	virtual GLvoid draw();
    GLvoid setAngle(GLfloat angle);
    GLvoid crash(GLfloat angle, GLfloat car_speed);
    virtual GLvoid update(GLdouble delta_t);
};