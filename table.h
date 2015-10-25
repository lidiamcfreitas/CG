#pragma once

#include "DynamicObject.h"

class Table: public DynamicObject{
public:
	Table();
	~Table();
	GLvoid draw();
};