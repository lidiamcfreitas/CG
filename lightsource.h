#pragma once
#include "vector3.h"
#include <array>

class lightsource{

private:
	GLfloat _param_light_model[4];
	GLfloat _ambient[4];
	GLfloat _diffuse[4];
	GLfloat _specular[4];

public:
	lightsource();
	~lightsource();
};

