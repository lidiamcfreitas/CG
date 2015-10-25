#include "movperspectivecamera.h"
#include <iostream>

Movperspectivecamera::Movperspectivecamera(GLdouble near, GLdouble far): Perspectivecamera(near, far){
	_up.set(0, 0, 1);
}


Movperspectivecamera::~Movperspectivecamera(){
}

GLvoid Movperspectivecamera::update(Vector3 vec, Vector3 speed ){
	_position.set(vec.getX() - (speed.getX()*75)/speed.norm(), vec.getY()- (speed.getY()*75)/speed.norm(), 100);
	_looking.set(vec.getX(), vec.getY(), 20);

}