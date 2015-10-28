#pragma once

#include "vector3.h"

class Camera{

protected:
	GLdouble _near;
	GLdouble _far;

public:
	Camera(GLdouble near, GLdouble far);
	Camera();
	~Camera();
	virtual GLvoid update(Vector3 vec, GLfloat angle);
	virtual GLvoid computeProjectionMatrix(GLfloat aspect);
	virtual GLvoid computeVisualizationMatrix();
};

