#include "lightsource.h"


Lightsource::Lightsource(GLint num){
	_ambient.set(1.0, 1.0, 1.0, 1.0);
	_diffuse.set(1.0, 1.0, 1.0, 1.0);
    _specular.set(1.0, 1.0, 1.0, 1.0);
    _direction.set(0, 0, -1);
    _cut_off = 85;
    _exponent = 1.7;
    _id = num;
    _on = false;
}

Lightsource::~Lightsource(){}

GLvoid Lightsource::draw(){
    GLfloat position[] = {(GLfloat) getPositionX(), (GLfloat) getPositionY(),(GLfloat) getPositionZ(), 0};
    if (_id) {
        position[3] = 1; // put last value of position to 1, if pointlight
    }
    
    GLfloat ambient[] = {_ambient.getX(),_ambient.getY(),_ambient.getZ(),_ambient.getW()};
    GLfloat specular[] = {_specular.getX(),_specular.getY(),_specular.getZ(),_specular.getW()};
    GLfloat diffuse[] = {_diffuse.getX(),_diffuse.getY(),_diffuse.getZ(),_diffuse.getW()};
    
    glLightfv(GL_LIGHT0 + _id, GL_POSITION, position);
    glLightfv(GL_LIGHT0 + _id, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0 + _id, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0 + _id, GL_DIFFUSE, diffuse);
    
    if (_id==0) return;
    
    GLfloat direction[] = {(GLfloat)_direction.getX(),(GLfloat)_direction.getY(),(GLfloat)_direction.getZ()};
    
    glLightfv(GL_LIGHT0 + _id, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0 + _id, GL_SPOT_CUTOFF, _cut_off);
    glLightf(GL_LIGHT0 + _id, GL_SPOT_EXPONENT, _exponent);
    if (_id==7) {
        glLightf(GL_LIGHT0 + _id, GL_QUADRATIC_ATTENUATION, 0.0003);
    }
}

GLvoid Lightsource::update(Car car){
	Vector3 direction = Vector3(cos(car.getAngle()*M_PI / 180), sin(car.getAngle()*M_PI / 180), 0);
	_direction.set(direction.getX() / direction.norm(), direction.getY() / direction.norm(), 0);
	setPosition(_direction.getX()*3 + car.getPositionX(),_direction.getY()*3 + car.getPositionY(), .5 + car.getPositionZ());
}

GLvoid Lightsource::setDirection(GLdouble x, GLdouble y, GLdouble z){
    _direction.set(x, y, z);
}

GLvoid Lightsource::setCutOff(GLfloat cut_off){
    _cut_off = cut_off;
}
GLvoid Lightsource::setExponent(GLfloat exponent){
    _exponent=exponent;
}
GLvoid Lightsource::setAmbient(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    _ambient.set(x, y, z, w);
}
GLvoid Lightsource::setDiffuse(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    _diffuse.set(x, y, z, w);
}
GLvoid Lightsource::setSpecular(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    _specular.set(x, y, z, w);
}

GLvoid Lightsource::setOn(GLboolean on){
    _on = on;
    if(_on)
        glEnable(GL_LIGHT0 + _id);
    else
        glDisable(GL_LIGHT0 + _id);
}

GLvoid Lightsource::switchOn(){
    setOn(!_on);
}

GLboolean Lightsource::getOn(){
    return _on;
}




