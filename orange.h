#pragma once

#include "dynamicobject.h"


class Orange : public DynamicObject{
private:
    GLfloat     _orange_angle;
    GLfloat     _orange_vel;
    GLfloat     _rotate;
    GLboolean   _shadow;
    GLint       _last_time_division;
    GLboolean   _alive;
    GLint       _id;
public:
    Orange(GLint i);
	~Orange();
	virtual GLvoid draw();
    GLvoid update(GLdouble delta_t);
    GLvoid wakeupOrange();
    GLvoid levelUp();
    GLvoid switchShadow();
};