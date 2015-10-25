#pragma once
#include "definitions.h"

class Vector3{

protected:			//talvez deva ser private
	GLdouble _x;
	GLdouble _y;
	GLdouble _z;

public:
	Vector3();
	Vector3( GLdouble x, GLdouble y, GLdouble z);
	~Vector3();
	GLdouble const getX();
	GLdouble const getY();
	GLdouble const getZ();
	GLvoid set(GLdouble x, GLdouble y, GLdouble z);
    GLvoid set(Vector3 &arg);
	GLboolean operator== (const Vector3 &vec);
	Vector3 operator* (GLdouble num);
	Vector3 operator+ (const Vector3 &vec);
	Vector3 operator- (const Vector3 &vec);
	GLdouble norm();
    GLfloat angle();
};


