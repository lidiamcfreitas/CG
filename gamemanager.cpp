#include "gamemanager.h"


GameManager::GameManager() {
    rotate_x = -65;
    rotate_y = 0;
	_light_calculation = false;
    _daylight = true;
    _itsOver = false;
}

GameManager::~GameManager(){
    
}

GLboolean GameManager::getKeyUp(){ return _car.getKeyUp(); }
GLboolean GameManager::getKeyDown(){ return _car.getKeyDown(); }
GLboolean GameManager::getKeyRight(){ return _car.getKeyRight(); }
GLboolean GameManager::getKeyLeft(){ return _car.getKeyLeft(); }
GLboolean GameManager::itsOver() { return _itsOver; }
GLvoid GameManager::setKeyUp(GLboolean value){ _car.setKeyUp(value); }
GLvoid GameManager::setKeyDown(GLboolean value){ _car.setKeyDown(value); }
GLvoid GameManager::setKeyRight(GLboolean value){ _car.setKeyRight(value); }
GLvoid GameManager::setKeyLeft(GLboolean value){ _car.setKeyLeft(value); }


GLvoid GameManager::keyPressed(unsigned char key){
    switch (key){
        // EXTRA - ROTACAO
        case 'e':
            rotate_x += 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        case 'd':
            rotate_x -= 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        case 's':
            rotate_y += 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        case 'f':
            rotate_y -= 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        
        // PROJECTO
        case '1':
            _currentCamera = CAMERA_ORTHO;
            changedCamera();
            rotate_x = 0;
            rotate_y = 0;
            break;
        case '2':
            _currentCamera = CAMERA_PERSP;
            changedCamera();
            rotate_x = -65.;
            rotate_y = 0.;
            break;
            
        case '3':
            _currentCamera = CAMERA_CAR;
            changedCamera();
            rotate_x = 0;
            rotate_y = 0;
            break;
            
        case 'a':
            changeSolidOrWire(); //flip boolean
            break;
            
		case 'l':
			_light_calculation = !_light_calculation;
			lightCalculationChanged();
            
            for (int i=0; i<NUM_ORANGES;i++){ // To remove artificial shadow when calculation on
                _oranges[i].switchShadow();
            }
			break;
		case 'g':
			//TODO Alterar entre constante e Gouraud
			break;
		case 'n':
			//TODO Ligar ou desligar iluminacao global
            _daylight = !_daylight;
            _lightsources[0].switchOn();
			break;
            
        case 'c':
            Vector4 emiss = Vector4(0.0, 0.0, 0.0, 1.0);
            
            for (int i = 1; i < _pointlights.size(); i++){
                _lightsources[i].switchOn();              // without lightsource 0
                
                if(_pointlights[i].getEmissionX()==0)
                    emiss.set(0.5, 0.5, 0.5, 0.0);
                else
                    emiss.set(0.0, 0.0, 0.0, 1.0);
            
                _pointlights[i].setMatEmission(emiss.getX(), emiss.getY(), emiss.getZ(), emiss.getW());
            }
    }
    
}

GLvoid GameManager::lightCalculationChanged(){
	if (_light_calculation == true)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}

GLvoid GameManager::changeSolidOrWire(){
    _car.changeSolidOrWire();
    
    for (int i = 0; i < _butters.size(); i++)
        _butters[i].changeSolidOrWire();
    
    for (int i = 0; i < _oranges.size(); i++)
        _oranges[i].changeSolidOrWire();
}

GLvoid GameManager::display(GLboolean solidOrWire) {
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	_cameras[_currentCamera]->computeVisualizationMatrix();

    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
    /* TODO - TIRAR */
    GLfloat amb_shelter[]={0.02f,0.02f,0.02f,1.0f};
    GLfloat diff_shelter[]={0.01f,0.01f,0.01f,1.0f};
    GLfloat spec_shelter[]={0.4f,0.4f,0.4f,1.0f};
    GLfloat shine_shelter=10.0f;
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb_shelter);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff_shelter);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec_shelter);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine_shelter);
    
    GLfloat emiss[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, emiss);
    glTranslatef(ROAD_OUT_RADIUS-ROAD_WIDTH/2, 0, ROAD_WIDTH/6);
    glScalef(ROAD_WIDTH/3, 10, ROAD_WIDTH/3);
    glColor4b(0, 0, 0, 0.5);
    glBegin(GL_QUADS);
    
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.5f, -1.0f, 1.5f);
    glVertex3f(1.5f, -1.0f, 1.5f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    glVertex3f(-1.5f, 1.0f, 1.5f);
    
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.5f, -1.0f, -1.5f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    glVertex3f(1.5f, -1.0f, 1.5f);
    
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    glVertex3f(-1.5f, 1.0f, -1.5f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    glVertex3f(1.5f, -1.0f, -1.5f);
    
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    glVertex3f(-1.5f, -1.0f, 1.5f);
    glVertex3f(-1.5f, 1.0f, 1.5f);
    glVertex3f(-1.5f, 1.0f, -1.5f);
    
    glEnd();
    
    glPopMatrix();

    _table.draw();
    _car.draw();
    
    for (int i = 0; i < _butters.size(); i++)
        _butters[i].draw();
    
    for (int i = 0; i < _oranges.size(); i++)
        _oranges[i].draw();
    for (int i = 0; i < _cheerios_in.size(); i++)
        _cheerios_in[i].draw();
    
    for (int i = 0; i < _cheerios_out.size(); i++)
        _cheerios_out[i].draw();
    
    for (int i = 0; i < _lightsources.size(); i++)
        _lightsources[i].draw();
    
    for (int i = 0; i < _pointlights.size(); i++)
        _pointlights[i].draw();
    
    glFlush();
    glutSwapBuffers(); /* TIRAR */
    
}

GLvoid GameManager::reshape(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	_cameras[_currentCamera]->computeProjectionMatrix();
}

GLvoid GameManager::changedCamera(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	_cameras[_currentCamera]->computeProjectionMatrix();
}

GLvoid GameManager::update(GLdouble delta_t){
    
    if (_car.getLives()<=0) {
        _itsOver = true;
    }
    
    //update positions
    _car.update(delta_t);
    
    for (int i = 0; i < _butters.size(); i++)
        _butters[i].update(delta_t);
    
    for (int i = 0; i < _oranges.size(); i++)
        _oranges[i].update(delta_t);
    for (int i = 0; i < _cheerios_in.size(); i++)
        _cheerios_in[i].update(delta_t);
    
    for (int i = 0; i < _cheerios_out.size(); i++)
        _cheerios_out[i].update(delta_t);

	//update current camera
	_cameras[_currentCamera]->update(_car.getPosition(), _car.getAngle());
    
    //update lightsource
    _lightsources[7].update(_car);
    //_lightsources[8].update(_car);
    
    //collisions
    
    Vector3 direction = Vector3();
    for( GLint i = 0; i < NUM_ORANGES; i++){ // car - oranges
        if(detectCollision(_car, _oranges[i], direction)){
            //printf("collision detected with oranges\n");
            _car.reset();
            break;
        }
    }
    
    for( GLint i = 0; i < _cheerios_in.size(); i++){
        if(detectCollision(_car, _cheerios_in[i], direction)){
            //printf("collision detected with cheerios_in\n");
            _cheerios_in[i].crash(direction.angle(),_car.getVel());
            _car.crash();
        }
    }
    
    for( GLint i = 0; i < _cheerios_out.size(); i++){
        if(detectCollision(_car, _cheerios_out[i], direction)){
            //printf("collision detected with cheerios_out\n");
            _cheerios_out[i].crash(direction.angle(),_car.getVel());
            _car.crash();
        }
    }
    for( GLint i = 0; i < _cheerios_in.size(); i++){
        for( GLint j = 0; j < _cheerios_in.size(); j++){
            if(i!=j && detectCollision(_cheerios_in[i], _cheerios_in[j], direction)){
                //printf("collision detected with cheerios_in\n");
                _cheerios_in[j].crash(direction.angle(),10);
                _cheerios_in[i].crash(direction.angle()+180,5);
            }
        }
    }
    
    for( GLint i = 0; i < _cheerios_out.size(); i++){
        for( GLint j = 0; j < _cheerios_out.size(); j++){
            if(i!=j && detectCollision(_cheerios_out[i], _cheerios_out[j], direction)){
                //printf("collision detected with cheerios_in\n");
                _cheerios_out[j].crash(direction.angle(),5);
                _cheerios_out[i].crash(direction.angle()+180,5);
            }
        }
    }
    
    for( GLint i = 0; i < _cheerios_in.size(); i++){
        for( GLint j = 0; j < _cheerios_out.size(); j++){
            if(i!=j && detectCollision(_cheerios_in[i], _cheerios_out[j], direction)){
                //printf("collision detected with cheerios_in\n");
                _cheerios_in[i].crash(direction.angle()+180,5);
                _cheerios_out[j].crash(direction.angle(),5);
            }
        }
    }
    
    for( GLint i = 0; i < _butters.size(); i++){
        if(detectCollision(_car, _butters[i], direction)){
            //printf("collision detected with butters\n");
            _butters[i].crash(direction.angle(),_car.getVel());
            _car.crash();
        }
    }
    
}

GLboolean GameManager::detectCollision(DynamicObject &obj1, DynamicObject &obj2, Vector3 &direction_v){
    direction_v =  obj1.getPosition() - obj2.getPosition();
    GLdouble norm = direction_v.norm();
    GLdouble sum_hitboxes = obj1.getHitboxRadius() + obj2.getHitboxRadius();
    
    
    return norm < sum_hitboxes;
}

GLvoid GameManager::init(){

	//Lighting set up


	//Cameras set up
	_cameras.push_back(std::make_shared<Orthocamera>());
	_cameras.push_back(std::make_shared<Perspectivecamera> (1, PRESPCAM_POS + TABLE_SIZE));
	_cameras.push_back(std::make_shared<Movperspectivecamera>(1, 300));
	_currentCamera = CAMERA_PERSP;
    GLdouble angleIncrement = ((2 * M_PI) / (2 * NUM_CHEERIOS));
    GLdouble lightIncrement =((2 * M_PI) / NUM_POINTLIGHTS);
    
    /*
    GLdouble angleIncrement = ((2 * M_PI) / (2 * NUM_CHEERIOS));*/
    srand((unsigned int)time(NULL));
    
    //car
    _car = Car();
    
    //outter cheerios
    for(float angle = 0; angle < 2 * M_PI - angleIncrement; angle = angle + angleIncrement){
        Cheerio cheerio = Cheerio(angle, ROAD_OUT_RADIUS);
        _cheerios_out.push_back(cheerio);
    }
    //inner cheerios
    for(float angle = 0; angle < 2 * M_PI - angleIncrement; angle = angle + 2 * angleIncrement){
        Cheerio cheerio = Cheerio(angle, ROAD_OUT_RADIUS - ROAD_WIDTH);
        _cheerios_in.push_back(cheerio);
    }
    //oranges
    for(int i = 0; i < NUM_ORANGES; i++){
        Orange orange = Orange(i);
        _oranges.push_back(orange);
    }
    //butters
    for(int i = 0; i < NUM_BUTTERS; i++){
        Butter butter = Butter();
        _butters.push_back(butter);
    }
    //Game table
    _table = Table();
    
    
    // Light Source 0
    Lightsource lightsource = Lightsource(0);
    lightsource.setPosition(1,0,1);
    lightsource.setDirection(0, 0, -1);
    lightsource.setAmbient(0.8, 0.8, 0.8, 1);
    lightsource.setDiffuse(0.5, 0.5, 0.5, 1);
    lightsource.setSpecular(0.2, 0.2, 0.2, 1);
    _lightsources.push_back(lightsource);
    
    
    //point lights
    GLint i = 1;
    for(float angle = 0; angle < 2 * M_PI - lightIncrement; angle = angle + lightIncrement){
        Pointlight pointlight = Pointlight(RADIUS_POINTLIGHTS * cosf(angle), RADIUS_POINTLIGHTS * sinf(angle), 0);
        _pointlights.push_back(pointlight);
        
        Lightsource lightsource = Lightsource(i);
        lightsource.setPosition(pointlight.getPositionX(), pointlight.getPositionY(), pointlight.getPositionZ()+20);
        _lightsources.push_back(lightsource);
        i++;
    }
    lightsource = Lightsource(7);
    lightsource.setPosition(_car.getPositionX(),_car.getPositionY(),_car.getPositionZ());
    //GLfloat norm = _car.getSpeed().norm();
    //lightsource.setDirection(_car.getSpeed().getX()/norm, _car.getSpeed().getY()/norm, _car.getSpeed().getZ()/norm);
    _lightsources.push_back(lightsource);
    //_lightsources.push_back(Lightsource(8));
    
}

GLvoid GameManager::levelUp(){
    //oranges
    for(int i = 0; i < NUM_ORANGES; i++){
        _oranges[i].levelUp();
    }
}

GLvoid GameManager::wakeupOrange(int _id){
    _oranges[_id].wakeupOrange();
}
