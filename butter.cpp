#include "butter.h"

Butter::Butter():DynamicObject(){
    setPosition((rand()%(TABLE_SIZE) - TABLE_SIZE/2), (rand()%(TABLE_SIZE) - TABLE_SIZE/2), 2.0);
    setAngle( (rand() % 180) );
    _hitboxRadius = 5.34;//5.34
};

Butter::~Butter(){};

GLvoid Butter::setAngle(GLfloat angle){ _angle = angle;}

GLvoid Butter::draw(){
    GLboolean solidOrWire = getSolidOrWire();//Solid or Wire objects flag

    glPushMatrix();
    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef( getPosition().getX(), getPosition().getY(), 2.0f);
    glRotatef(_angle, 0.0f, 0.0f, 1.0f);
    glScalef(2.6f, 1.5f, 1.3f);
    
    if(solidOrWire)
        glutSolidCube(4);
    else
        glutWireCube(4);
    
    glPopMatrix();
    glPopMatrix();
}

GLvoid Butter::crash(GLfloat angle, GLfloat car_speed){
    _vel = std::abs(car_speed*2); // cheerio half mass of car
    _angle = angle + 180;
}

GLvoid Butter::update(GLdouble delta_t){
    
    GLdouble delta_x = cos(_angle*M_PI/180)*_vel*delta_t/1000;
    GLdouble delta_y = sin(_angle*M_PI/180)*_vel*delta_t/1000;
    
    
    if(_vel < 0)// making sure he stays put when he should
        _vel = 0;
    else{
        _vel = _vel - 1.5 * BUTTER_DEACCEL * delta_t/1000;
        setPosition(getPosition().getX()+delta_x, getPosition().getY()+delta_y, getPosition().getZ());
    }
}