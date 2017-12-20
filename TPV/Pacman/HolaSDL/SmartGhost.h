#pragma once
#include "Ghost.h"
#include "Game.h"
#include <cstdlib>
using namespace std;

static const int tamanyoBaby = 10;
static const int edadAdulta = 100;
static const int edadMuerte = 200;

class SmartGhost : public Ghost
{
private:
	int age;
	bool adult;
	bool deadState;
	int ancho, alto;
	int fertilidad;
	//Dirs direcciones[4] = { { 0, -1 }, { -1, 0 }, { 0, 1 }, { 1, 0 } }; //Array de direcciones para el pathfinding

public:
	SmartGhost();
	SmartGhost(int orX, int orY, int numFant, Texture* text, Game* gam, int edad, int type);
	~SmartGhost();

	virtual void update(); //Cambiamos el cambiaDir de los fantasmas originales, por lo que redefinimos update
	void changeDir(); //Cambia la direccion para seguir a Pacman
	bool backward(int dirX, int dirY); //Comprueba que la nueva dirección no sea la contraria y sólo la coja si no se puede mover atrás
	bool reproduce(); //Devuelve true si adult está a true
	void crece();
	void olddie();
	virtual bool dead();
};

