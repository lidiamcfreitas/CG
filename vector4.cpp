#include "Vector4.h"
#include <math.h>
Vector4::Vector4(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
	_x = x;
	_y = y;
	_z = z;
    _w = w;
}

Vector4::Vector4(){

}

Vector4::~Vector4() {}

GLfloat const Vector4::getX() { return _x; } //Saber como o const funciona
GLfloat const Vector4::getY() { return _y; }
GLfloat const Vector4::getZ() { return _z; }
GLfloat const Vector4::getW() { return _w; }

GLvoid Vector4::set(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
	_x = x;
	_y = y;
	_z = z;
    _w = w;
}

GLvoid Vector4::set(Vector4 &arg){
    _x = arg.getX();
    _y = arg.getY();
    _z = arg.getZ();
    _z = arg.getW();
}

GLboolean Vector4::operator== (const Vector4 &vec){
	return (_x == vec._x && _y == vec._y && _z == vec._z && _w == vec._w);
}

Vector4 Vector4::operator* (GLfloat num){
	Vector4 resultVec = Vector4();
	resultVec._x = _x * num;
	resultVec._y = _y * num;
	resultVec._z = _z * num;
    resultVec._w = _w * num;
	return resultVec;

}

Vector4 Vector4::operator+ (const Vector4 &vec){
	Vector4 resultVec = Vector4();
	resultVec._x = _x + vec._x;
	resultVec._y = _y + vec._y;
	resultVec._z = _z + vec._z;
    resultVec._w = _w + vec._w;
	return resultVec;
}

Vector4 Vector4::operator- (const Vector4 &vec){
	Vector4 resultVec = Vector4();
	resultVec._x = _x - vec._x;
	resultVec._y = _y - vec._y;
	resultVec._z = _z - vec._z;
    resultVec._w = _w - vec._w;
	return resultVec;
}

GLfloat Vector4::norm(){
	return sqrt(_x*_x + _y*_y + _z*_z + _w*_w);
}

GLfloat Vector4::angle(){
    return atan2(_y, _x) * 180 / M_PI;
}