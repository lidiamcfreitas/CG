#include "carlives.h"


Carlives::Carlives(){
	_livesLeft = LIVES;
	int distance = 0;
	for (int i = 0; i < LIVES; i++){
		Car car = Car();
		car.setPosition(distance, 0, 0);
		_cars.push_back(car);
		distance -= 10;
	}
	_camera = std::make_shared<Orthocamera>(10);
}


Carlives::~Carlives(){
}

GLvoid Carlives::downOne(){
	_livesLeft -= 1;
}

GLint Carlives::getLives(){
	return _livesLeft;
}

GLvoid Carlives::draw(){
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	_camera->computeProjectionMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(14, 9, 0);
	glScalef(.05, .05, 0);
	for (int i = 0; i < _livesLeft; i++){
		_cars[i].draw();
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
