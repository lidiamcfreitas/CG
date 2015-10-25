#pragma once

#include "dynamicobject.h"


class Orange : public DynamicObject{
public:
    Orange();
	~Orange();
	virtual GLvoid draw();
    GLvoid update(GLdouble delta_t);
private:
    GLfloat     _orange_angle;
    GLfloat     _orange_vel;
    GLfloat       _rotate;
    GLint       _last_time_division;
};