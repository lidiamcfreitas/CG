#include "dynamicobject.h"

DynamicObject::DynamicObject() : GameObject(){
    _solidOrWire = true;
	_speed = Vector3(0, 0, 0);
}
DynamicObject::~DynamicObject() {}

GLvoid DynamicObject::update(GLdouble delta_t){}

GLvoid DynamicObject::setSpeed(Vector3 &speed){
	_speed.set(speed.getX(), speed.getY(), speed.getZ());
}

GLvoid DynamicObject::setSpeed(GLdouble x, GLdouble y, GLdouble z){
	_speed.set(x, y, z);
}

Vector3 DynamicObject::getSpeed(){
	return _speed;
}

GLboolean DynamicObject::getSolidOrWire(){
    return _solidOrWire;
}

GLvoid DynamicObject::changeSolidOrWire(){
    _solidOrWire = !_solidOrWire;
}

GLfloat DynamicObject::getHitboxRadius(){
    return _hitboxRadius;
}

GLvoid DynamicObject::setVel(GLdouble vel){
    _vel = vel;
}

GLvoid DynamicObject::setAngle(GLdouble angle){
    _angle = angle;
}

GLdouble DynamicObject::getAngle(){
    return _angle;
}

GLdouble DynamicObject::getVel(){
    return _vel;
}