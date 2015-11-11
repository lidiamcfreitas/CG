#pragma once
#include "definitions.h"

class Vector4{

protected:
	GLfloat _x;
	GLfloat _y;
	GLfloat _z;
    GLfloat _w;

public:
	Vector4();
	Vector4( GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	~Vector4();
	GLfloat const getX();
	GLfloat const getY();
	GLfloat const getZ();
    GLfloat const getW();
	GLvoid set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    GLvoid set(Vector4 &arg);
	GLboolean operator== (const Vector4 &vec);
	Vector4 operator* (GLfloat num);
	Vector4 operator+ (const Vector4 &vec);
	Vector4 operator- (const Vector4 &vec);
	GLfloat norm();
    GLfloat angle();
};


