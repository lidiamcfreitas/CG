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
    GLfloat amb[]={0.42f,0.41f,0.0745f,1.0f};
    GLfloat diff[]={0.75164f,0.60648f,0.28f,1.0f};
    GLfloat spec[]={0.53f,0.555802f,0.366065f,1.0f};
    GLfloat shine=51.2f;

    
    glPushMatrix();
    material(amb, diff, spec, shine);
    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef( getPositionX(), getPositionY(), getPositionZ()+ 2.0f);
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
        /* AND NOW FALLING FROM THE TABLE :( */
        if (fabs(getPositionX()) >(TABLE_SIZE/2+4) || fabs(getPositionY()) >(TABLE_SIZE/2+4)) {
            setPosition(getPositionX() + delta_x, getPositionY() + delta_y, getPositionZ()-2);
        } else {
            _vel = _vel - 1.5 * BUTTER_DEACCEL * delta_t/1000;
            setPosition(getPositionX()+delta_x, getPositionY()+delta_y, getPositionZ());
        }
    }
}