#include "movperspectivecamera.h"
#include <iostream>

Movperspectivecamera::Movperspectivecamera(GLdouble near, GLdouble far): Perspectivecamera(near, far){
	_up.set(0, 0, 1);
}


Movperspectivecamera::~Movperspectivecamera(){
}

GLvoid Movperspectivecamera::update(Vector3 vec, Vector3 speed, GLdouble vel ){
    GLfloat x = speed.getX()*75/speed.norm();
    GLfloat y = speed.getY()*75/speed.norm();
    
    if (vel <0){
        _position.set(vec.getX() + x, vec.getY() + y, 100);
    } else {
        _position.set(vec.getX() - x, vec.getY()- y, 100);
    }
    
	_looking.set(vec.getX(), vec.getY(), 20);

}