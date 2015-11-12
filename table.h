#pragma once

#include "DynamicObject.h"
#include "math.h"

class Table: public DynamicObject{
public:
	Table();
	~Table();
	GLvoid draw();
};