#include "gamemanager.h"


GameManager::GameManager() {
    rotate_x = -65;
    rotate_y = 0;
	_light_calculation = false;
    _daylighte = false;
    _itsOver = false;
	_shadingRegular = true;
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
        case 'i':
            rotate_x += 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        case 'k':
            rotate_x -= 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        case 'p':
            rotate_y += 5;
            printf("rotate %f, %f\n", rotate_x, rotate_y);
            break;
        case 'j':
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
		
		case 'h':
			_lightsources[7].switchOn();
			break;

		case 'l':
			_light_calculation = !_light_calculation;
			lightCalculationChanged();

            if (!_light_calculation && _daylighte){
                _lightsources[0].setOn(false);
                _daylighte = !_daylighte;
            }
            
            for (int i=0; i<NUM_ORANGES;i++){ // To remove artificial shadow when calculation is on
                _oranges[i].switchShadow();
            }
            
            if (!_light_calculation)
                glClearColor( 65./255, 105./255, 1., 0.);
            else
                glClearColor(0, 51./255, 102./255, 0);
            
			break;
		case 'g':
			_shadingRegular = !_shadingRegular;
			if (_shadingRegular)
				glShadeModel(GL_FLAT);
			else
				glShadeModel(GL_SMOOTH);
			break;
		case 'n':
            
            if (_light_calculation) {
                _daylighte = !_daylighte;
                _lightsources[0].switchOn();
                
                if (_daylighte)
                    glClearColor( 65./255, 105./255, 1., 0.);
                else
                    glClearColor(0, 51./255, 102./255, 0);
            }
			break;
            
        case 'c':
            Vector4 emiss = Vector4(0.0, 0.0, 0.0, 1.0);
            
            for (int i = 1; i < _lightsources.size()-1; i++){  
                _lightsources[i].switchOn();              // without lightsource 0
				
                if(_lightsources[i].getOn())
                    emiss.set(0.5, 0.5, 0.5, 0.0);
                else
                    emiss.set(0.0, 0.0, 0.0, 1.0);
            
                _pointlights[i-1].setMatEmission(emiss.getX(), emiss.getY(), emiss.getZ(), emiss.getW());
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
    
	_carLives.draw();

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
    
    if (_carLives.getLives()<=0) {
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
    
    //update carlight
    _lightsources[7].update(_car);
    
    //collisions
    
    Vector3 direction = Vector3();
    for( GLint i = 0; i < NUM_ORANGES; i++){ // car - oranges
        if(detectCollision(_car, _oranges[i], direction)){
            //printf("collision detected with oranges\n");
            _car.reset();
			_carLives.downOne();
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

	if (_car.getCarFell()){
		_carLives.downOne();
		_car.changeCarFell();
	}

}

GLboolean GameManager::detectCollision(DynamicObject &obj1, DynamicObject &obj2, Vector3 &direction_v){
    direction_v =  obj1.getPosition() - obj2.getPosition();
    GLdouble norm = direction_v.norm();
    GLdouble sum_hitboxes = obj1.getHitboxRadius() + obj2.getHitboxRadius();
    
    
    return norm < sum_hitboxes;
}

GLvoid GameManager::init(){
	glShadeModel(GL_FLAT);
	glDisable(GL_LIGHTING);

	//Cameras set up
	_cameras.push_back(std::make_shared<Orthocamera>(ORTHO_SIZE));
	_cameras.push_back(std::make_shared<Perspectivecamera> (1, PRESPCAM_POS + TABLE_SIZE));
	_cameras.push_back(std::make_shared<Movperspectivecamera>(1, 300));
	_currentCamera = CAMERA_PERSP;
	changedCamera();
    GLdouble angleIncrement = ((2 * M_PI) / (2 * NUM_CHEERIOS));
    GLdouble lightIncrement =((2 * M_PI) / NUM_POINTLIGHTS);
    
    /*
    GLdouble angleIncrement = ((2 * M_PI) / (2 * NUM_CHEERIOS));*/
    srand((unsigned int)time(NULL));
    
    //car
    _car = Car();
	_carLives = Carlives();

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

	//car lights
    lightsource = Lightsource(7);
	lightsource.update(_car);
	lightsource.setCutOff(25);
	lightsource.setExponent(20);
	_lightsources.push_back(lightsource); 

	//textures
	Texture texture = Texture();
	texture.loadTexture("ground.png");
	_texture.push_back(texture);
	texture = Texture();
	texture.loadTexture("pausa.png");
	_texture.push_back(texture);
	texture = Texture();
	texture.loadTexture("gameover.png");
	_texture.push_back(texture);
	setNormalTexture();
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

GLvoid GameManager::setPauseTexture(){
	glBindTexture(GL_TEXTURE_2D, _texture[1].getTexture());
}

GLvoid GameManager::setNormalTexture(){
	glBindTexture(GL_TEXTURE_2D, _texture[0].getTexture());
}

GLvoid GameManager::setRestartTexture(){
	glBindTexture(GL_TEXTURE_2D, _texture[2].getTexture());
}

GLvoid GameManager::setCamera(GLint cameraNumber){
	_currentCamera = cameraNumber;
}