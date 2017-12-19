#pragma once
#include "Ghost.h"
#include "Game.h"

class SmartGhost : public Ghost
{
private:
	int age;
	bool adult;
	//Dirs direcciones[4] = { { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 } }; //Array de direcciones para el pathfinding

public:
	SmartGhost();
	SmartGhost(int orX, int orY, int numFant, Texture* text, Game* gam, int edad);
	~SmartGhost();

	virtual void update(); //Cambiamos el cambiaDir de los fantasmas originales, por lo que redefinimos update
	//virtual void animar(bool vitamina);
	//virtual void render();
	void changeDir(); //Cambia la direccion para seguir a Pacman
	bool reproduce(); //Devuelve true si adult está a true
	//virtual void loadFromFile(ifstream& file);
};

