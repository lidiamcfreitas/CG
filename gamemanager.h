#pragma once

#include "gameobject.h"
#include "dynamicobject.h"
#include "gameobject.h"
#include "vector3.h"
#include "table.h"
#include "car.h"
#include "cheerio.h"
#include "orange.h"
#include "butter.h"
#include "camera.h"
#include "orthocamera.h"
#include "perspectivecamera.h"
#include "movperspectivecamera.h"


class GameManager{

private:
    Car _car;
    Table _table;
    
    std::vector<Cheerio> _cheerios_out;
    std::vector<Cheerio> _cheerios_in;
    std::vector<Orange> _oranges;
    std::vector<Butter> _butters;
    
	int _currentCamera;
	GLsizei _w, _h;
    /* TODO missing light_sources */
    
    GLboolean _solidOrWire;
    GLdouble rotate_y;
    GLdouble rotate_x;
public:
    std::vector<Camera*> _cameras;
    GameManager();
    ~GameManager();
    GLvoid display(GLboolean solidOWire);
    GLvoid reshape(GLsizei w, GLsizei h);
	GLvoid keyPressed(unsigned char key);
    GLvoid update(GLdouble delta_t);
    GLvoid init();
    GLboolean getKeyUp();
    GLboolean getKeyDown();
    GLboolean getKeyRight();
    GLboolean getKeyLeft();
    GLvoid setKeyUp(GLboolean value);
    GLvoid setKeyDown(GLboolean value);
    GLvoid setKeyRight(GLboolean value);
    GLvoid setKeyLeft(GLboolean value);
    GLvoid changeSolidOrWire();
	GLvoid changedCamera();
    GLboolean detectCollision(DynamicObject &obj1index, DynamicObject &obj2index, Vector3 &direction_v);
    GLvoid objectReaction(GLint obj1index, GLint obj2index);
    GLvoid wakeupOrange(int _id);
};
