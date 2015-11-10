#include "gamemanager.h"


GameManager::GameManager() {
    rotate_x = -65;
    rotate_y = 0;
}

GameManager::~GameManager(){
    
}

GLboolean GameManager::getKeyUp(){ return _car.getKeyUp(); }
GLboolean GameManager::getKeyDown(){ return _car.getKeyDown(); }
GLboolean GameManager::getKeyRight(){ return _car.getKeyRight(); }
GLboolean GameManager::getKeyLeft(){ return _car.getKeyLeft(); }
GLvoid GameManager::setKeyUp(GLboolean value){ _car.setKeyUp(value); }
GLvoid GameManager::setKeyDown(GLboolean value){ _car.setKeyDown(value); }
GLvoid GameManager::setKeyRight(GLboolean value){ _car.setKeyRight(value); }
GLvoid GameManager::setKeyLeft(GLboolean value){ _car.setKeyLeft(value); }

GLvoid GameManager::keyPressed(unsigned char key){
    switch (key){
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
        case 'e':
            rotate_x += 5;
            break;
        case 'd':
            rotate_x -= 5;
            break;
        case 's':
            rotate_y += 5;
            break;
        case 'f':
            rotate_y -= 5;
            break;
        case 'a':
            changeSolidOrWire(); //flip boolean
            break;
    }
    printf("%f, %f\n", rotate_x, rotate_y);
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
    
    //collisions
    
    Vector3 direction = Vector3();
    for( GLint i = 0; i < NUM_ORANGES; i++){ // car - oranges
        if(detectCollision(_car, _oranges[i], direction)){
            printf("collision detected with oranges\n");
            _car.reset();
            break;
        }
    }
    
    for( GLint i = 0; i < _cheerios_in.size(); i++){
        if(detectCollision(_car, _cheerios_in[i], direction)){
            printf("collision detected with cheerios_in\n");
            _cheerios_in[i].crash(direction.angle(),_car.getVel());
            _car.crash();
        }
    }
    
    for( GLint i = 0; i < _cheerios_out.size(); i++){
        if(detectCollision(_car, _cheerios_out[i], direction)){
            printf("collision detected with cheerios_out\n");
            _cheerios_out[i].crash(direction.angle(),_car.getVel());
            _car.crash();
        }
    }
    for( GLint i = 0; i < _cheerios_in.size(); i++){
        for( GLint j = 0; j < _cheerios_in.size(); j++){
            if(i!=j && detectCollision(_cheerios_in[i], _cheerios_in[j], direction)){
                printf("collision detected with cheerios_in\n");
                _cheerios_in[j].crash(direction.angle(),10);
                _cheerios_in[i].crash(direction.angle()+180,5);
            }
        }
    }
    
    for( GLint i = 0; i < _cheerios_out.size(); i++){
        for( GLint j = 0; j < _cheerios_out.size(); j++){
            if(i!=j && detectCollision(_cheerios_out[i], _cheerios_out[j], direction)){
                printf("collision detected with cheerios_in\n");
                _cheerios_out[j].crash(direction.angle(),5);
                _cheerios_out[i].crash(direction.angle()+180,5);
            }
        }
    }
    
    for( GLint i = 0; i < _cheerios_in.size(); i++){
        for( GLint j = 0; j < _cheerios_out.size(); j++){
            if(i!=j && detectCollision(_cheerios_in[i], _cheerios_out[j], direction)){
                printf("collision detected with cheerios_in\n");
                _cheerios_in[i].crash(direction.angle()+180,5);
                _cheerios_out[j].crash(direction.angle(),5);
            }
        }
    }
    
    for( GLint i = 0; i < _butters.size(); i++){
        if(detectCollision(_car, _butters[i], direction)){
            printf("collision detected with butters\n");
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
    
    //point lights
    for(float angle = 0; angle < 2 * M_PI - lightIncrement; angle = angle + lightIncrement){
        printf("x: %d y: %d angle: %d\n", RADIUS_POINTLIGHTS * cosf(angle), RADIUS_POINTLIGHTS * sinf(angle), angle);
        Pointlight pointlight = Pointlight(RADIUS_POINTLIGHTS * cosf(angle), RADIUS_POINTLIGHTS * sinf(angle), 0);
        _pointlights.push_back(pointlight);
    }
    
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
