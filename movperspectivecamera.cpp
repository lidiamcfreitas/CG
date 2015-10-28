#include "movperspectivecamera.h"
#include <iostream>

Movperspectivecamera::Movperspectivecamera(GLdouble near, GLdouble far): Perspectivecamera(near, far){
	_up.set(0, 0, 1);
}


Movperspectivecamera::~Movperspectivecamera(){
}

GLvoid Movperspectivecamera::update(Vector3 vec, GLfloat angle ){
	GLfloat x = cos(angle*M_PI / 180) * 75;
	GLfloat y = sin(angle*M_PI / 180) * 75;
    

    _position.set(vec.getX() - x, vec.getY()- y, 100);
    
	_looking.set(vec.getX(), vec.getY(), 20);

}
