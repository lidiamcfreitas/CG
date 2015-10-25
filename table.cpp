#include "table.h"

Table::Table() {}
Table::~Table() {}
GLvoid Table::draw(){
	
    
    //start line
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(ROAD_OUT_RADIUS - ROAD_WIDTH/2, 0, -0.4);
    glScalef(ROAD_WIDTH - (CHEERIO_RADIUS + CHEERIO_RADIUS_TUBE), 2, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    //table
    glColor3f(0.528, 0.528, 0.528); // glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslatef( 0.0f, 0.0f, -20.);
    
    glScalef(1, 1, 40./TABLE_SIZE);
	glutSolidCube(TABLE_SIZE);
    glPopMatrix();
}