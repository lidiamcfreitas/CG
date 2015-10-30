#include "movperspectivecamera.h"
#include <iostream>

Movperspectivecamera::Movperspectivecamera(GLdouble near, GLdouble far): Perspectivecamera(near, far){
	_up.set(0, 0, 1);
}


Movperspectivecamera::~Movperspectivecamera(){
}

GLvoid Movperspectivecamera::update(Vector3 vec, GLfloat angle ){
	GLfloat x = cos(angle*M_PI / 180) * DISTANCE_CAM_TO_CAR;
	GLfloat y = sin(angle*M_PI / 180) * DISTANCE_CAM_TO_CAR;
    

    _position.set(vec.getX() - x, vec.getY()- y, HEIGHT_CAM_TO_CAR);
    
	_looking.set(vec.getX(), vec.getY(), 20);

}

GLvoid Movperspectivecamera::computeVisualizationMatrix(){
	GLdouble aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT));

	if (aspect >= 0.5){
		gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
			_looking.getX(), _looking.getY(), _looking.getZ(),
			_up.getX(), _up.getY(), _up.getZ());
	}
	else{
		gluLookAt(_position.getX(), _position.getY(), _position.getZ()/(aspect*2),
			_looking.getX(), _looking.getY(), _looking.getZ(),
			_up.getX(), _up.getY(), _up.getZ());
	}
}

