#include "camera.h"

Camera::Camera(GLdouble near, GLdouble far){
	_near = near;
	_far = far;
}

Camera::Camera(){}

Camera::~Camera(){}

GLvoid Camera::update(Vector3 vec, Vector3 speed){
}

GLvoid Camera::computeProjectionMatrix(GLfloat aspect){
}

GLvoid Camera::computeVisualizationMatrix(){
}