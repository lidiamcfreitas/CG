#pragma once
#include "vector4.h"
#include "vector3.h"
#include "gameobject.h"
#include "car.h"
#include <array>

class Lightsource: public GameObject{

private:
    Vector4 _param_light_model;
	Vector4 _ambient;
	Vector4 _diffuse;
	Vector4 _specular;
    Vector3 _direction;
    GLfloat	_cut_off;
    GLfloat _exponent;
    GLboolean _on;
    GLint   _id;

public:
	Lightsource(GLint num);
	~Lightsource();
    GLvoid draw();
    GLvoid setDirection(GLdouble x, GLdouble y, GLdouble z);
    GLvoid setCutOff(GLfloat cut_off);
    GLvoid setExponent(GLfloat exponent);
    GLvoid setAmbient(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    GLvoid setDiffuse(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    GLvoid setSpecular(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    GLvoid setOn(GLboolean on);
    GLvoid switchOn();
    GLboolean getOn();
    GLvoid update(Car car);
    
    
};

