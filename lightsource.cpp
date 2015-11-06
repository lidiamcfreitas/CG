#include "lightsource.h"


lightsource::lightsource(){
	/*_param_light_model = {0.2f, 0.2f, 0.2f, 1.0 };
	_ambient = { 0.0, 0.1, 0.0, 1.0 };
	_diffuse = { 0.0, 1.0, 1.0, 1.0 };
	_specular = { 1.0, 1.0, 1.0, 1.0 };*/
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, _param_light_model);
	glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);
}


lightsource::~lightsource()
{
}
