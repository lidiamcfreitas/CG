#pragma once

#include "Camera.h"

class Orthocamera: public Camera {
private:
	int _orthoSize;
public:
	Orthocamera(int size);
	~Orthocamera();
	GLvoid computeProjectionMatrix();
};

