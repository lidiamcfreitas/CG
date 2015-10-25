#include "gameobject.h"

GameObject::GameObject(){}

GameObject::~GameObject(){}

GLvoid GameObject::draw(){}

GLvoid GameObject::update(GLdouble delta_t){};

Vector3 GameObject::getPosition(){
    return _position;
}

Vector3 GameObject::setPosition(GLdouble x, GLdouble y, GLdouble z){
    _position.set(x, y, z);
    return _position;
}

Vector3 GameObject::setPosition(Vector3 &p){
    _position.set(p.getX(), p.getY(), p.getZ());
    return _position;
}