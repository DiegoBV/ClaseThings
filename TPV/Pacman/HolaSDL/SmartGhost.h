#pragma once
#include "Ghost.h"
#include "Game.h"
static const int tamanyoBaby = 10;
static const int edadAdulta = 50;
class SmartGhost : public Ghost
{
private:
	int age;
	bool adult;
	int ancho, alto;
	//Dirs direcciones[4] = { { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 } }; //Array de direcciones para el pathfinding

public:
	SmartGhost();
	SmartGhost(int orX, int orY, int numFant, Texture* text, Game* gam, int edad);
	~SmartGhost();

	virtual void update(); //Cambiamos el cambiaDir de los fantasmas originales, por lo que redefinimos update
	//virtual void animar(bool vitamina);
	//virtual void render();
	void changeDir(); //Cambia la direccion para seguir a Pacman
	bool backward(int dirX, int dirY); //Comprueba que la nueva direcci�n no sea la contraria y s�lo la coja si no se puede mover atr�s
	bool reproduce(); //Devuelve true si adult est� a true
	void crece();
	//virtual void loadFromFile(ifstream& file);
};

