#include "perspectivecamera.h"


Perspectivecamera::Perspectivecamera(GLdouble near, GLdouble far) : Camera(near, far){
	_position = Vector3(0, 0, PRESPCAM_POS);
	_looking = Vector3(0, 0, -1);
	_up = Vector3(0, 1, 0);
}


Perspectivecamera::~Perspectivecamera(){
}


GLvoid Perspectivecamera::computeProjectionMatrix(){
	GLdouble aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT));
	if (aspect >= 1)
		gluPerspective(FOV_Y, aspect, _near, _far);
	else
		gluPerspective(FOV_Y, aspect, (_near/aspect), (_far/aspect));
}

GLvoid Perspectivecamera::computeVisualizationMatrix(){
	GLdouble aspect = float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT));

	if (aspect >= 1){
		gluLookAt(_position.getX(), _position.getY(), _position.getZ(),
			_looking.getX(), _looking.getY(), _looking.getZ(),
			_up.getX(), _up.getY(), _up.getZ());
	}
	else{
		gluLookAt(_position.getX()/aspect, _position.getY()/aspect, (_position.getZ()/aspect),
			_looking.getX(), _looking.getY(), _looking.getZ(),
			_up.getX(), _up.getY(), _up.getZ());
	}
}
