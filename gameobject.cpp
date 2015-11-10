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

GLvoid GameObject::material(GLfloat amb[], GLfloat diff[], GLfloat spec[], GLfloat shine) {
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
    
    GLfloat emi[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, emi);
}