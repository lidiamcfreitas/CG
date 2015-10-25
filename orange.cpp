#include "orange.h"

Orange::Orange():DynamicObject(){
    _hitboxRadius = 5;//2.5
    _orange_angle = rand() % 360;
    _orange_vel = ORANGE_INI_VEL + rand()%ORANGE_INI_VEL;
    _rotate = 0;
    _last_time_division = 0;
    setPosition((rand()%(TABLE_SIZE) - TABLE_SIZE/2), (rand()%(TABLE_SIZE) - TABLE_SIZE/2), ORANGE_SIZE);
};

Orange::~Orange() {
    
};

GLvoid Orange::draw(){
    GLboolean solidOrWire = getSolidOrWire();//Solid or Wire objects flag
    
    
    glPushMatrix();

    glTranslatef( getPosition().getX(), getPosition().getY(), getPosition().getZ());
    glRotatef(_rotate,(-1)*sin(_orange_angle*M_PI/180),cos(_orange_angle*M_PI/180),0);
    
    //------------orange
    glColor3f(0.992, 0.6039, 0);
    
    glPushMatrix();

    if(solidOrWire){ // radius 5
        glutSolidSphere(ORANGE_SIZE, 16, 16);
    }
    else{
        glutWireSphere(ORANGE_SIZE, 16, 16);
    }
    glPopMatrix();
        
    

    
    //----------stick
    glColor3f(65./255, 73.0/255, 47./255);
    glPushMatrix();
    
    glTranslatef( 0, 0, ORANGE_SIZE);
    glRotatef(15, 0, 1, 0);
    glScalef(1, 1, 3.5); //3.5 or 7 (pau GRANDE - lidia aproves)
    if(solidOrWire){
        glutSolidCube(ORANGE_SIZE/7.);
    }
    else{
        glutWireCube(ORANGE_SIZE/7.);
    }
    glPopMatrix();
    
    //----------folha
    glColor3f(96./255, 147./255, 71./255);
    glPushMatrix();
    
    glTranslatef( ORANGE_SIZE*0.35, 0, ORANGE_SIZE*1.);
    glRotatef(40, 0, 1, 1);
    glScalef(1.4, 1, 0.1);
    if(solidOrWire){
        glutSolidCube(ORANGE_SIZE/3.);
    }
    else{
        glutWireCube(ORANGE_SIZE/3.);
    }
    glPopMatrix();
    glPopMatrix();
    
    if (getPosition().getZ()>0) {
        //----Sombra
        glColor3f(0.4, 0.4, 0.4);
        glPushMatrix();
        glTranslatef( getPosition().getX(), getPosition().getY(), 1);
        glRotatef(90, 0, 1, 0);
        glutSolidSphere((1-getPosition().getZ()/360)*ORANGE_SIZE, 2, 16);
        glPopMatrix();
    }
}

GLvoid Orange::update(GLdouble delta_t){
    
    GLdouble currentTime = glutGet(GLUT_ELAPSED_TIME);
    if ((GLint)currentTime/10000 != _last_time_division) {
        _orange_vel = _orange_vel + rand() % ORANGE_VEL_STEP;
    }
    
    //_orange_vel = _orange_vel + ORANGE_ACCEL * delta_t/1000;// defines forward acceleration
        
    GLdouble delta_x = cos(_orange_angle*M_PI/180)*_orange_vel*delta_t/1000;
    GLdouble delta_y = sin(_orange_angle*M_PI/180)*_orange_vel*delta_t/1000;
    
    /* I SEE ORANGES FALLING FROM THE SKY */
    if (getPosition().getZ()>ORANGE_SIZE) {
        setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ() -1);
    } else {
        setPosition(getPosition().getX() + delta_x, getPosition().getY() + delta_y, getPosition().getZ());
    }
    
    
    
    /* AND NOW FALLING FROM THE TABLE :( */
    if (fabs(getPosition().getX()) >(TABLE_SIZE/2+ORANGE_SIZE*0.5) || fabs(getPosition().getY()) >(TABLE_SIZE/2+ORANGE_SIZE*0.5)) {
        setPosition(getPosition().getX() + delta_x, getPosition().getY() + delta_y, getPosition().getZ()-1);
    }
    if ((fabs(getPosition().getX()) >(TABLE_SIZE/2 + ORANGE_SIZE*0.5) || fabs(getPosition().getY()) >(TABLE_SIZE/2 + ORANGE_SIZE*0.5)) &&  getPosition().getZ()<-100) {
        setPosition((rand()%(TABLE_SIZE) - TABLE_SIZE/2), (rand()%(TABLE_SIZE) - TABLE_SIZE/2), ORANGE_SIZE+300);
    }
    
    _rotate += _orange_vel*(delta_t/1000)*360/(2.*M_PI*ORANGE_SIZE);
    _last_time_division = (GLint)currentTime/10000;
}