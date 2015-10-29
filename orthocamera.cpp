#include "orthocamera.h"

Orthocamera::Orthocamera(): Camera() {}

Orthocamera::~Orthocamera(){}

GLvoid Orthocamera::computeProjectionMatrix(){
	GLdouble aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT));
	
	if (aspect >= 1) {
		glOrtho(-1 * ORTHO_SIZE * aspect, ORTHO_SIZE * aspect, -1 * ORTHO_SIZE, ORTHO_SIZE, -1 * ORTHO_SIZE, ORTHO_SIZE);
	}
	else{
		glOrtho(-1 * ORTHO_SIZE, ORTHO_SIZE, -1 * ORTHO_SIZE / aspect, ORTHO_SIZE / aspect, -1 * ORTHO_SIZE, ORTHO_SIZE);
	}
}
