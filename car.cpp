#include "car.h"
#include <iostream>
#include <stdlib.h>

Car::Car(): DynamicObject() {
    _vel = 0;
    _angle = 90;
    _up = false;
    _down = false;
    _right = false;
    _left = false;
    _previous_position  = Vector3();
    _hitboxRadius = 7.04;//7.04
    _lives = LIVES;
    setPosition(95, -6.5, 0);//95,-6.5,0
	setSpeed(0, 1, 0);
}

Car::~Car() {};

GLboolean Car::getKeyUp(){ return _up; }
GLboolean Car::getKeyDown(){ return _down; }
GLboolean Car::getKeyRight(){ return _right; }
GLboolean Car::getKeyLeft(){ return _left; }
GLvoid Car::setKeyUp(GLboolean value){ _up = value; }
GLvoid Car::setKeyDown(GLboolean value){ _down = value; }
GLvoid Car::setKeyRight(GLboolean value){ _right = value; }
GLvoid Car::setKeyLeft(GLboolean value){ _left = value; }
GLint Car::getLives(){ return _lives; }
GLvoid Car::crash(){
    setPosition(_previous_position.getX(), _previous_position.getY(), _previous_position.getZ());
    _vel = 0;
}

GLvoid Car::reset(){
    crash();
    _up = false;
    _down = false;
    _right = false;
    _left = false;
    _angle = 90;
    setPosition(95, -6.5, 0);//95,-6.5,0
    setSpeed(0, 1, 0);
    printf("lost a life\n");
    _lives--;
}

GLvoid Car::draw(){
    
    GLboolean solidOrWire = getSolidOrWire();
    
    GLfloat amb[]={0.0215f,0.1745f,0.0215f,1.0f};
    GLfloat diff[]={0.07568f,0.47f,0.07568f,1.0f};
    GLfloat spec[]={0.633f,0.727811f,0.633f,1.0f};
    GLfloat shine=76.8f;
    
    GLfloat amb_red[]={0.1745f,0.01175f,0.01175f,1.0f};
    GLfloat diff_red[]={0.61424f,0.04136f,0.04136f,1.0f};
    GLfloat spec_red[]={0.727811f,0.626959f,0.626959f,1.0f};
    GLfloat shine_red=76.8f;

	glPushMatrix();
    
    glTranslatef(getPositionX(), getPositionY(), getPositionZ());
    glRotatef(_angle-90, 0.0, 0.0, 1.0);
    
    //---------------------------------------main body
    glColor3f(0.0, 0.5, 0.0);//dark green
	glPushMatrix();
    material(amb, diff, spec, shine);
    glTranslatef(0.0, 0.0, 3.0);
    glScalef(1.0f, 1.2f, 0.7f);
    
    if(solidOrWire)
        glutSolidCube(5);
    else
        glutWireCube(5);
    
	glPopMatrix();

    //---------------------------------------front body
    glColor3f(0.0, 0.5, 0.0);//dark green
	glPushMatrix();
    material(amb, diff, spec, shine);
    glTranslatef(0.0, 4.0, 1.3f);
    glScalef(1.5f, 1.0f, 1.0f);
    if(solidOrWire) {
        glutSolidCube(2);
    }
    else{
        glutWireCube(2);
    }
	glPopMatrix();

    //---------------------------------------back body
    glColor3f(0.0,  0.5, 0.0);//dark green
	glPushMatrix();
    material(amb, diff, spec, shine);
    glTranslatef(0.0, 3.5, 2.1);
    glScalef(3.0f, 1.0f, 3.5f);
    if(solidOrWire){
        glutSolidCube(1);
    }
    else{
        glutWireCube(1);
    }
	glPopMatrix();

    //--------------------------------------front axis
    glColor3f(0.7, 0.0, 0.0);//red
    glPushMatrix();
    material(amb_red, diff_red, spec_red, shine_red);
    glTranslatef(0.0, 4.5, 1.5f);
    glScalef(26.0f, 1.0f, 1.0f);
    if(solidOrWire){
        glutSolidCube(0.25);
    }
    else{
        glutWireCube(0.25);
    }
    glPopMatrix();
    
    drawWheel(2.7, 4.5, 1.6, 0.6, 1.0, solidOrWire);//front right wheel
    drawWheel(-2.7, 4.5, 1.6, 0.6, 1.0, solidOrWire);//front left wheel
    drawWheel(3.0, -3.0, 3.2, 1.2, 2.0, solidOrWire);//back right wheel
    drawWheel(-3.0, -3.0, 3.2, 1.2, 2.0, solidOrWire);//back left wheel

    glPopMatrix();
    
    glPopMatrix();
}

GLvoid Car::drawWheel(GLfloat wheelx, GLfloat wheely, GLfloat wheelz, GLfloat wheelInner, GLfloat wheelOuter, GLboolean solidOrWire){
    GLfloat amb_wheel[]={0.02f,0.02f,0.02f,1.0f};
    GLfloat diff_wheel[]={0.01f,0.01f,0.01f,1.0f};
    GLfloat spec_wheel[]={0.4f,0.4f,0.4f,1.0f};
    GLfloat shine_wheel=10.0f;
    
    GLfloat xtilt = 0.0;
    glColor3f(0.26, 0.15, 0.2);//dark grey
    glPushMatrix();
    material(amb_wheel, diff_wheel, spec_wheel, shine_wheel);
    if(_right && wheelOuter == 1.0){
        xtilt = -0.3;
    }
    else if(_left && wheelOuter == 1.0){
        xtilt = 0.3;
    }
    glTranslatef(wheelx, wheely, wheelz);
    glRotatef(90.0f, 0.0f, 1.0f, xtilt);
    if(solidOrWire){
        glutSolidTorus(wheelInner, wheelOuter, 9, 15);
    }
    else{
        glutWireTorus(wheelInner, wheelOuter, 9, 15);
    }
    glPopMatrix();
}

GLvoid Car::update(GLdouble delta_t){
    
    _previous_position.set(getPositionX(), getPositionY(), getPositionZ());
    GLboolean felloff = false;
    
    GLdouble delta_x = cos(_angle*M_PI/180)*_vel*delta_t/1000;
    GLdouble delta_y = sin(_angle*M_PI/180)*_vel*delta_t/1000;
    GLdouble delta_z = 0;
	if (_vel != 0 && std::abs(_vel) > 3)
		setSpeed(delta_x, delta_y, delta_z);
    
    if (fabs(getPositionX()) >(125. + _hitboxRadius*0.7 ) || fabs(getPositionY()) >(125. + _hitboxRadius*0.7 )) {
        setPosition(getPositionX() + delta_x, getPositionY() + delta_y, getPositionZ()-1.5);
        felloff = true;
    } else {
        if (!felloff) {
            setPosition(getPositionX() + delta_x, getPositionY() + delta_y, getPositionZ() + delta_z);
            if(_up && _vel < CAR_VEL_MAX){
                _vel = _vel + CAR_ACCEL * delta_t/1000;// defines forward acceleration
            }
            if (_down && _vel > CAR_VEL_MIN) {
                _vel = _vel - 1.9 * CAR_ACCEL * delta_t/1000;// defines backward acceleration
            }
            if(!_down && !_up && _vel > 0){
                _vel = _vel - 1.5 * CAR_ACCEL * delta_t/1000;// defines self forward de-acceleration
            }
            if(!_down && !_up && _vel < 0){
                _vel = _vel + 0.4 * CAR_ACCEL * delta_t/1000;// defines self backward de-acceleration
            }
            if (_left && std::abs(_vel) > 4){
                _angle = _angle + CAR_ANGLE_STEP * delta_t/1000;// defines steering left
            }
            if (_right && std::abs(_vel) > 4){
                _angle = _angle - CAR_ANGLE_STEP * delta_t/1000;// defines steering right
            }
            if(!_up && !_down && std::abs(_vel) < 0.1){// making sure he stays put when he should
                _vel = 0;
            }
        }
    }
    if ((fabs(getPositionX()) >(125. + _hitboxRadius*0.7 ) || fabs(getPositionY()) >(125. + _hitboxRadius*0.7 )) &&  getPositionZ()<-70) {
        felloff = false;
        printf("lost a life\n");
        _lives--;
        setPosition(95.0, -6.5, 0.0); // Initial position
        setVel(0.0);
        setAngle(90.0);
        setSpeed(0, 1, 0);
    }
}
