#include "cheerio.h"



Cheerio::Cheerio(GLfloat angle, GLint radius) : DynamicObject(){
    setRgb((rand()%50 + 50)/100.0, (rand()%50 + 50)/100.0, (rand()%50 + 50)/100.0);
    setPosition(radius * cosf(angle), radius * sinf(angle), -0.125);
    
    _vel = 0;
    _angle = 0;
    _hitboxRadius = CHEERIO_RADIUS_TUBE + CHEERIO_RADIUS;
}//1.125

Cheerio::~Cheerio() {}

GLvoid Cheerio::draw(){

    glPushMatrix();
    
    glColor3f(_r, _g, _b);
    
    glPushMatrix();
    glTranslatef(getPosition().getX(), getPosition().getY(), CHEERIO_RADIUS_TUBE);
    glutSolidTorus(CHEERIO_RADIUS_TUBE, CHEERIO_RADIUS, 6, 15); //0.25, 1.0, 6, 15
    glPopMatrix();
    
    glPopMatrix();
 }

GLvoid Cheerio::setRgb(GLfloat r, GLfloat g, GLfloat b){
    _r = r;
    _g = g;
    _b = b;
}

GLvoid Cheerio::crash(GLfloat angle, GLfloat car_speed){
    _vel = std::abs(car_speed/CHEERIO_REL_MASS); // cheerio half mass of car
    _angle = angle + 180;
}

GLvoid Cheerio::update(GLdouble delta_t){
    
    GLdouble delta_x = cos(_angle*M_PI/180)*_vel*delta_t/1000;
    GLdouble delta_y = sin(_angle*M_PI/180)*_vel*delta_t/1000;

    
    if(_vel < 0)// making sure he stays put when he should
        _vel = 0;
    else{
        _vel = _vel - 1.5 * CHEERIO_DEACCEL * delta_t/1000;
        setPosition(getPosition().getX()+delta_x, getPosition().getY()+delta_y, getPosition().getZ());
    }
}