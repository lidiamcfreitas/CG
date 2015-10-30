#pragma once

#include "camera.h"

class Perspectivecamera: public Camera{

protected:
	Vector3 _position;
	Vector3 _looking;
	Vector3 _up;

public:
	Perspectivecamera(GLdouble near, GLdouble far);
	~Perspectivecamera();
	virtual GLvoid computeProjectionMatrix();
	virtual GLvoid computeVisualizationMatrix();
};

