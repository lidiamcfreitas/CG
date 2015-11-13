#include "pointlight.h"

Pointlight::Pointlight(GLdouble x, GLdouble y, GLdouble z) {
    setPosition(x, y, z);
    _mat_emiss.set(0, 0, 0, 1);
}

Pointlight::~Pointlight(){}

GLvoid Pointlight::draw(){
    
    GLfloat ambient_head[]= {0.5f,0.0f,0.0f,1.0f};
    GLfloat diffuse_head[]= {0.5f,0.4f,0.4f,1.0f};
    GLfloat specular_head[]= {0.7f,0.04f, 0.04f,1.0f};
    GLfloat shine_head= 10.0f;
    
    
    GLfloat amb_stick[]={0.329412f,0.223529f,0.027451f,1.0f};
    GLfloat diff_stick[]={0.32f,0.21f,0.113725f,1.0f};
    GLfloat spec_stick[]={0.0f,0.0f,0.0f,1.0f};
    GLfloat shine_stick=128.0f;
    
    glPushMatrix();
    glTranslatef(getPositionX(),getPositionY(),getPositionZ()+6.25);
    
    // MATCH HEAD
    glColor3f(176./255, 0, 6./255);
    glPushMatrix();
    material(ambient_head, diffuse_head, specular_head, shine_head);
    GLfloat emiss1[]={_mat_emiss.getX(),_mat_emiss.getY(),_mat_emiss.getZ(),_mat_emiss.getW()};
    glMaterialfv(GL_FRONT, GL_EMISSION, emiss1);
    glTranslatef(0, 0, 19.8/2);
    glScalef(0.7, 0.7, 1);
    glutSolidSphere(2, 16, 16);
    glPopMatrix();
    
    // MATCH STICK
    glColor3f(234./255, 206./255, 164./255);
    glPushMatrix();
    material(amb_stick, diff_stick, spec_stick, shine_stick);
    glScalef(1, 1, 20);
    glutSolidCube(1);
    glPopMatrix();
    

    
    glPopMatrix();
}

GLfloat Pointlight::getEmissionX(){
    return _mat_emiss.getX();
}

GLvoid Pointlight::setMatEmission(GLfloat x, GLfloat y, GLfloat z, GLfloat w){
    _mat_emiss.set(x, y, z, w);
}
