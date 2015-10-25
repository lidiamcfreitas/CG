#pragma once
#include "dynamicObject.h"

class Cheerio : public DynamicObject{
private:
    GLfloat _r;
    GLfloat _g;
    GLfloat _b;

public:
	Cheerio(GLfloat angle, GLint radius);
	~Cheerio();
    virtual GLvoid draw();
    virtual GLvoid setRgb(GLfloat r, GLfloat g, GLfloat b);
    virtual GLvoid update(GLdouble delta_t);
    GLvoid crash(GLfloat angle, GLfloat car_speed);
};