#include "vector3.h"
#include <math.h>
Vector3::Vector3(GLdouble x, GLdouble y, GLdouble z){
	_x = x;
	_y = y;
	_z = z;
}

Vector3::Vector3(){

}

Vector3::~Vector3() {}

GLdouble const Vector3::getX() { return _x; } //Saber como o const funciona
GLdouble const Vector3::getY() { return _y; }
GLdouble const Vector3::getZ() { return _z; }

GLvoid Vector3::set(GLdouble x, GLdouble y, GLdouble z){
	_x = x;
	_y = y;
	_z = z;
}

GLvoid Vector3::set(Vector3 &arg){
    _x = arg.getX();
    _y = arg.getY();
    _z = arg.getZ();
}

GLboolean Vector3::operator== (const Vector3 &vec){
	return (_x == vec._x && _y == vec._y && _z == vec._z);
}

Vector3 Vector3::operator* (GLdouble num){
	Vector3 resultVec = Vector3();
	resultVec._x = _x * num;
	resultVec._y = _y * num;
	resultVec._z = _z * num;
	return resultVec;

}

Vector3 Vector3::operator+ (const Vector3 &vec){
	Vector3 resultVec = Vector3();
	resultVec._x = _x + vec._x;
	resultVec._y = _y + vec._y;
	resultVec._z = _z + vec._z;
	return resultVec;
}

Vector3 Vector3::operator- (const Vector3 &vec){
	Vector3 resultVec = Vector3();
	resultVec._x = _x - vec._x;
	resultVec._y = _y - vec._y;
	resultVec._z = _z - vec._z;
	return resultVec;
}

GLdouble Vector3::norm(){
	return sqrt(_x*_x + _y*_y + _z*_z);
}

GLfloat Vector3::angle(){
    return atan2(_y, _x) * 180 / M_PI;
}