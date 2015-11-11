#include "cheerio.h"



Cheerio::Cheerio(GLfloat angle, GLint radius) : DynamicObject(){
    setRgb((rand()%50 + 50)/100.0, (rand()%50 + 50)/100.0, (rand()%50 + 50)/100.0);
    setPosition(radius * cosf(angle), radius * sinf(angle), -0.125);
    randomMaterial();
    _vel = 0;
    _angle = 0;
    _hitboxRadius = CHEERIO_RADIUS_TUBE + CHEERIO_RADIUS;
}//1.125

Cheerio::~Cheerio() {}

GLvoid Cheerio::draw(){
    
    glPushMatrix();
    
    glColor3f(_r, _g, _b);
    
    GLfloat ambient[] = {_amb.getX(),_amb.getY(),_amb.getZ(),_amb.getW()};
    GLfloat specular[] = {_spec.getX(),_spec.getY(),_spec.getZ(),_spec.getW()};
    GLfloat diffuse[] = {_diff.getX(),_diff.getY(),_diff.getZ(),_diff.getW()};
    material(ambient, diffuse, specular, _shine);
    glPushMatrix();
    glTranslatef(getPositionX(), getPositionY(), getPositionZ() + CHEERIO_RADIUS_TUBE);
    glutSolidTorus(CHEERIO_RADIUS_TUBE, CHEERIO_RADIUS, 6, 15); //0.25, 1.0, 6, 15
    glPopMatrix();
    
    glPopMatrix();
 }

GLvoid Cheerio::setRgb(GLfloat r, GLfloat g, GLfloat b){
    _r = r;
    _g = g;
    _b = b;
}

GLvoid Cheerio::randomMaterial(){
    
    GLint random_color = rand()%4;
    _diff.set(0.4f,0.5f,0.5f,1.0f);
    _spec.set(0.04f,0.7f,0.7f,1.0f);
    _shine=10.0f;
    switch (random_color){
        case 0:
            _amb.set(0.0f,0.05f,0.05f,1.0f);
            break;
        case 1:
            _amb.set(0.47f,0.28f,0.05f,1.0f);
            break;
        case 2:
            _amb.set(0.0f,0.36f,0.05f,1.0f);
            break;
    }
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
        /* AND NOW FALLING FROM THE TABLE :( */
        if (fabs(getPositionX()) >(TABLE_SIZE/2+CHEERIO_RADIUS*0.5) || fabs(getPositionY()) >(TABLE_SIZE/2+CHEERIO_RADIUS*0.5)) {
            setPosition(getPositionX() + delta_x, getPositionY() + delta_y, getPositionZ()-1);
        } else {
            _vel = _vel - 1.5 * CHEERIO_DEACCEL * delta_t/1000;
            setPosition(getPositionX()+delta_x, getPositionY()+delta_y, getPositionZ());
        }
    }
}