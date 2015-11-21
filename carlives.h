#pragma once

#include "car.h"
#include "orthocamera.h"

class Carlives{
private:
	std::vector<Car> _cars;
	std::shared_ptr<Orthocamera> _camera;
	int _livesLeft;

public:
	Carlives();
	~Carlives();
	GLvoid downOne();
	GLvoid draw();
	GLint getLives();
};

