#pragma once

#include "perspectivecamera.h"

class Movperspectivecamera : public Perspectivecamera{


public:
	Movperspectivecamera(GLdouble near, GLdouble far);
	~Movperspectivecamera();
	GLvoid update(Vector3 vec, Vector3 speed);

};

