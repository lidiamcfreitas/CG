#pragma once
#include "dynamicObject.h"
#include "vector4.h"

class Cheerio : public DynamicObject{
private:
    GLfloat _r;
    GLfloat _g;
    GLfloat _b;
    Vector4 _amb;
    Vector4 _diff;
    Vector4 _spec;
    GLfloat _shine;

public:
	Cheerio(GLfloat angle, GLint radius);
	~Cheerio();
    virtual GLvoid draw();
    virtual GLvoid setRgb(GLfloat r, GLfloat g, GLfloat b);
    virtual GLvoid update(GLdouble delta_t);
    GLvoid crash(GLfloat angle, GLfloat car_speed);
    GLvoid randomMaterial();
};