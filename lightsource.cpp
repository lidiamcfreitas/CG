#include "lightsource.h"


Lightsource::Lightsource(GLint num){
    _param_light_model.set(0.2, 0.2, 0.2, 1);
	_ambient.set(1.0, 1.0, 1.0, 1);
	_diffuse.set(1.0,1.0,1.0,1.0);
    _specular.set(1.0,1.0,1.0,1.0);
    _direction.set(0, 0, -1);
    _cut_off = 75;
    _exponent = 2;
    _id = num;
    _on = false;
}


Lightsource::~Lightsource()
{
}

GLvoid Lightsource::draw(){
    GLfloat position[] = {(GLfloat) getPositionX(), (GLfloat) getPositionY(),(GLfloat) getPositionZ(), 1};
    //GLfloat ambColor[] = {_param_light_model.getX(),_param_light_model.getY(),_param_light_model.getZ(),_param_light_model.getW()};
    GLfloat ambient[] = {_ambient.getX(),_ambient.getY(),_ambient.getZ(),_ambient.getW()};
    GLfloat specular[] = {_specular.getX(),_specular.getY(),_specular.getZ(),_specular.getW()};
    GLfloat diffuse[] = {_diffuse.getX(),_diffuse.getY(),_diffuse.getZ(),_diffuse.getW()};
    
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambColor);
    glLightfv(GL_LIGHT0 + _id, GL_POSITION, position);
    glLightfv(GL_LIGHT0 + _id, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0 + _id, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0 + _id, GL_DIFFUSE,diffuse);
    
    if (_id==0) return;
    
    GLfloat direction[] = {(GLfloat)_direction.getX(),(GLfloat)_direction.getY(),(GLfloat)_direction.getZ()};
    glLightfv(GL_LIGHT0 + _id, GL_SPOT_DIRECTION, direction);
    
    glLightfv(GL_LIGHT0 + _id, GL_SPOT_CUTOFF, &_cut_off);
    
    glLightfv(GL_LIGHT0 + _id, GL_SPOT_EXPONENT, &_exponent);
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




