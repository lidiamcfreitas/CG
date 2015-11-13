#include "table.h"

Table::Table() {}
Table::~Table() {}
GLvoid Table::draw(){
    GLfloat amb[]={0.14f,0.14f,0.11f,1.0f};
    GLfloat diff[]={0.1f,0.13f,0.16f,1.0f};
    GLfloat spec[]={0.18f,0.2f,0.25f,1.0f};
    GLfloat shine=26;
    
    GLfloat amb_obsidian[]={0.05375f,0.05f,0.06625f,1.0f};
    GLfloat diff_obsidian[]={0.18275f,0.17f,0.22525f,1.0f};
    GLfloat spec_obsidian[]={0.332741f,0.328634f,0.346435f,1.0f};
    GLfloat shine_obsidian=38.4f;
    
    GLfloat amb_red[]={0.1745f,0.01175f,0.01175f,1.0f};
    GLfloat diff_red[]={0.61424f,0.04136f,0.04136f,1.0f};
    GLfloat spec_red[]={0.727811f,0.626959f,0.626959f,1.0f};
    GLfloat shine_red=76.8f;
    
    glPushMatrix();
    
    //start line
    glPushMatrix();
    glColor3f(1, 0, 0);
    material(amb_red, diff_red, spec_red, shine_red);
    glTranslatef(ROAD_OUT_RADIUS - ROAD_WIDTH/2, 0, -0.39);
    glScalef(ROAD_WIDTH - (CHEERIO_RADIUS + CHEERIO_RADIUS_TUBE), 2, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    //table
    glColor3f(0.6, 0.6, 0.6); // glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    material(amb, diff, spec, shine);
    glTranslatef( 0.0f, 0.0f, -20.);
    
    glScalef(1, 1, 40./TABLE_SIZE);
    glutSolidCube(TABLE_SIZE);
    glPopMatrix();
    
    //inner table circle
    glPushMatrix();
    glColor3f(0.6, 0.6, 0.6); // glColor3f(0.7, 0.7, 0.7);
    material(amb, diff, spec, shine);
    glTranslatef(0.0, 0.0, 0.11);
    glRotatef(90, 0, 1, 0);
    
    glBegin(GL_POLYGON);
    GLfloat degree = 25;
    GLfloat radius = ROAD_OUT_RADIUS - ROAD_WIDTH;
    glNormal3f(0,0, 1);

    for (GLint i=0; i<degree+1; i++) {
        GLfloat angle = (2*M_PI/degree)*i;
        glVertex3f(0,radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();
    glPopMatrix();
    
    //outter table ring
    glPushMatrix();
    glColor3f(0.428, 0.428, 0.428); // glColor3f(0.7, 0.7, 0.7);
    material(amb_obsidian, diff_obsidian, spec_obsidian, shine_obsidian);
    glTranslatef(0.0, 0.0, 0.1);
    glRotatef(90, 0, 1, 0);
    
    glBegin(GL_POLYGON);
    degree = 25;
    radius = ROAD_OUT_RADIUS;
    glNormal3f(0,0, 1);
    
    for (GLint i=0; i<degree+1; i++) {
        GLfloat angle = (2*M_PI/degree)*i;
        glVertex3f(0,radius * cosf(angle), radius * sinf(angle));
    }
    glEnd();
    glPopMatrix();
    
    glPopMatrix();
}