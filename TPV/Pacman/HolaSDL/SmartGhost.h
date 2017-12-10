#pragma once
#include "Ghost.h"
class Game;
class SmartGhost : public Ghost
{
private:
	int edad = 0;
	bool adulto;

public:
	SmartGhost();
	~SmartGhost();
	bool reproduce();
	void cambiaDir();
};

