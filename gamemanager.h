#pragma once

#include "gameobject.h"
#include "dynamicobject.h"
#include "vector3.h"
#include "vector4.h"
#include "table.h"
#include "car.h"
#include "cheerio.h"
#include "orange.h"
#include "butter.h"
#include "pointlight.h"
#include "lightsource.h"
#include "camera.h"
#include "orthocamera.h"
#include "perspectivecamera.h"
#include "movperspectivecamera.h"
#include "carlives.h"
#include "texture.h"


class GameManager{

private:
    Car _car;
    Table _table;
    
    std::vector<Cheerio> _cheerios_out;
    std::vector<Cheerio> _cheerios_in;
    std::vector<Orange> _oranges;
    std::vector<Butter> _butters;
    std::vector<Pointlight> _pointlights;
    std::vector<Lightsource> _lightsources;
    
	std::vector<std::shared_ptr<Camera>> _cameras;
	std::vector<Texture> _texture;
	int _currentCamera;
    
    GLboolean   _solidOrWire;
    GLdouble    rotate_y;
    GLdouble    rotate_x;
	GLboolean   _light_calculation;
    GLboolean   _daylighte;
    GLboolean   _itsOver;
	GLboolean	_shadingRegular;
	Carlives	_carLives;

public:
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
    GLboolean itsOver();
    GLvoid setKeyUp(GLboolean value);
    GLvoid setKeyDown(GLboolean value);
    GLvoid setKeyRight(GLboolean value);
    GLvoid setKeyLeft(GLboolean value);
    GLvoid changeSolidOrWire();
	GLvoid changedCamera();
    GLboolean detectCollision(DynamicObject &obj1index, DynamicObject &obj2index, Vector3 &direction_v);
    GLvoid objectReaction(GLint obj1index, GLint obj2index);
    GLvoid wakeupOrange(GLint _id);
    GLvoid levelUp();
	GLvoid lightCalculationChanged();
	GLvoid setPauseTexture();
	GLvoid setNormalTexture();
	GLvoid setRestartTexture();
	GLvoid setCamera(GLint cameraNumber);

};
