#pragma once

#include "Camera.h"

class Orthocamera: public Camera {
public:
	Orthocamera();
	~Orthocamera();
	GLvoid computeProjectionMatrix();
};

