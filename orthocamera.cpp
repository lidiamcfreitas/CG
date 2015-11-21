#include "orthocamera.h"

Orthocamera::Orthocamera(int orthoSize): Camera() {
	_orthoSize = orthoSize;
}

Orthocamera::~Orthocamera(){}

GLvoid Orthocamera::computeProjectionMatrix(){
	GLdouble aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT));
	
	if (aspect >= 1) {
		glOrtho(-1 * _orthoSize * aspect, _orthoSize * aspect, -1 * _orthoSize, _orthoSize, -1 * _orthoSize, _orthoSize);
	}
	else{
		glOrtho(-1 * _orthoSize, _orthoSize, -1 * _orthoSize / aspect, _orthoSize / aspect, -1 * _orthoSize, _orthoSize);
	}
}
