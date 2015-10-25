#pragma once

#include "definitions.h"
#include "vector3.h"
#include <vector>


class GameObject{

private:
    Vector3 _position;
    
public:
	GameObject();
	~GameObject();
	virtual GLvoid draw();
	virtual GLvoid update(GLdouble delta_t);
    Vector3 getPosition();
    Vector3 setPosition(GLdouble x, GLdouble y, GLdouble z);
    Vector3 setPosition(Vector3 &p);
};

