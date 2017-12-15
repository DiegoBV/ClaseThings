#pragma once
#include "Ghost.h"

class SmartGhost : public Ghost
{
private:
	int age;
	bool adult;

public:
	SmartGhost();
	SmartGhost(int orX, int orY, int numFant, Texture* text, Game* gam, int edad);
	~SmartGhost();

	virtual void update(); //Cambiamos el cambiaDir de los fantasmas originales, por lo que redefinimos update
	virtual void animar(bool vitamina);
	virtual void render();
	void changeDir(); //Cambia la direccion para
	virtual void loadFromFile(ifstream& file);
};

