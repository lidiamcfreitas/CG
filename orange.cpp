#include "orange.h"

Orange::Orange(GLint i):DynamicObject(){
    _id = i;
    _alive = true;
    _hitboxRadius = 5;//2.5
    _orange_angle = rand() % 360;
    _orange_vel = ORANGE_INI_VEL + rand()%ORANGE_INI_VEL;
    _rotate = 0;
    _shadow = true;
    _last_time_division = 0;
    setPosition((rand()%(TABLE_SIZE) - TABLE_SIZE/2), (rand()%(TABLE_SIZE) - TABLE_SIZE/2), ORANGE_SIZE);
};

Orange::~Orange() {
    
};

GLvoid Orange::draw(){
    GLfloat ambient_orange[]= {0.49f,0.34f,0.11f,1.0f};
    GLfloat diffuse_orange[]= {0.41f,0.3f,0.21f,1.0f};
    GLfloat specular_orange[]= {0.7f,0.04f,0.04f,1.0f};
    GLfloat shine_orange= 10.0f;
    
    GLfloat amb_leaf[]={0.0f,0.05f,0.0f,1.0f};
    GLfloat diff_leaf[]={0.4f,0.41f,0.0f,1.0f};
    GLfloat spec_leaf[]={0.04f,0.7f,0.04f,1.0f};
    GLfloat shine_leaf=10.0f;
    
    GLfloat amb_stick[]={0.329412f,0.223529f,0.027451f,1.0f};
    GLfloat diff_stick[]={0.32f,0.21f,0.113725f,1.0f};
    GLfloat spec_stick[]={0.0f,0.0f,0.0f,1.0f};
    GLfloat shine_stick=128.0f;
    
	if (_alive){
		GLboolean solidOrWire = getSolidOrWire();//Solid or Wire objects flag


		glPushMatrix();

		glTranslatef(getPositionX(), getPositionY(), getPositionZ());
		glRotatef(_rotate, (-1)*sin(_orange_angle*M_PI / 180), cos(_orange_angle*M_PI / 180), 0);

		//------------orange
		glColor3f(0.992, 0.6039, 0);

		glPushMatrix();
        material(ambient_orange, diffuse_orange, specular_orange, shine_orange);

		if (solidOrWire){ // radius 5
			glutSolidSphere(ORANGE_SIZE, 16, 16);
		}
		else{
			glutWireSphere(ORANGE_SIZE, 16, 16);
		}
		glPopMatrix();




		//----------stick
		glColor3f(65. / 255, 73.0 / 255, 47. / 255);
		glPushMatrix();
        material(amb_stick, diff_stick, spec_stick, shine_stick);
		glTranslatef(0, 0, ORANGE_SIZE);
		glRotatef(15, 0, 1, 0);
		glScalef(1, 1, 3.5); //3.5 or 7
		if (solidOrWire){
			glutSolidCube(ORANGE_SIZE / 7.);
		}
		else{
			glutWireCube(ORANGE_SIZE / 7.);
		}
		glPopMatrix();

		//----------folha
		glColor3f(96. / 255, 147. / 255, 71. / 255);
		glPushMatrix();
        material(amb_leaf, diff_leaf, spec_leaf, shine_leaf);
		glTranslatef(ORANGE_SIZE*0.35, 0, ORANGE_SIZE*1.);
		glRotatef(40, 0, 1, 1);
		glScalef(1.4, 1, 0.1);
		if (solidOrWire){
			glutSolidCube(ORANGE_SIZE / 3.);
		}
		else{
			glutWireCube(ORANGE_SIZE / 3.);
		}
		glPopMatrix();
		glPopMatrix();

		if (_shadow && getPositionZ() > 0) {
			//----Sombra
			glColor3f(0.4, 0.4, 0.4);
			glPushMatrix();
			glTranslatef(getPositionX(), getPositionY(), 1);
			glRotatef(90, 0, 1, 0);
			glutSolidSphere((1 - getPositionZ() / 360)*ORANGE_SIZE, 2, 16);
			glPopMatrix();
		}
	}
}

 GLvoid Orange::wakeupOrange(){
    _alive = true;
     setPosition((rand()%(TABLE_SIZE) - TABLE_SIZE/2), (rand()%(TABLE_SIZE) - TABLE_SIZE/2), ORANGE_SIZE+300);
}

GLvoid Orange::levelUp(){
    printf("Orange %d lvld up\n", _id);
    _orange_vel = _orange_vel + ORANGE_VEL_STEP;
}

GLvoid Orange::switchShadow(){
    _shadow = !_shadow;
}

GLvoid Orange::update(GLdouble delta_t){
    

    GLdouble currentTime = glutGet(GLUT_ELAPSED_TIME);
        
    GLdouble delta_x = cos(_orange_angle*M_PI/180)*_orange_vel*delta_t/1000;
    GLdouble delta_y = sin(_orange_angle*M_PI/180)*_orange_vel*delta_t/1000;
    
    /* I SEE ORANGES FALLING FROM THE SKY */
    if (getPositionZ()>ORANGE_SIZE) {
        setPosition(getPositionX(), getPositionY(), getPositionZ() -1);
    } else {
        setPosition(getPositionX() + delta_x, getPositionY() + delta_y, getPositionZ());
    }
    
    
    
    /* AND NOW FALLING FROM THE TABLE :( */
    if (fabs(getPositionX()) >(TABLE_SIZE/2+ORANGE_SIZE*0.5) || fabs(getPositionY()) >(TABLE_SIZE/2+ORANGE_SIZE*0.5)) {
        setPosition(getPositionX() + delta_x, getPositionY() + delta_y, getPositionZ()-1);
    }
    if (_alive && (fabs(getPositionX()) >(TABLE_SIZE/2 + ORANGE_SIZE*0.5) || fabs(getPositionY()) >(TABLE_SIZE/2 + ORANGE_SIZE*0.5)) &&  getPositionZ()<-100) {

        _alive = false;
        glutTimerFunc(3000, main_wakeupOrange, _id);     
    }
    
    
    _rotate += _orange_vel*(delta_t/1000)*360/(2.*M_PI*ORANGE_SIZE);
    _last_time_division = (GLint)currentTime/10000;
}

