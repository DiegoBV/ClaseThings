#pragma once
#include "ManagerTemplate.h"
#include "Asteroid.h"
class AsteroidsManager
{
private:
	ManagerTemplate<Asteroid*>* listaAsteroides; //cambiar GO x gameObject, no sé si se hereda o se incluye la template
	SDLGame* game;
public:
	AsteroidsManager();
	~AsteroidsManager();
	AsteroidsManager(SDLGame* game) : game(game) {};
	void updatePool();
	bool renovarPool();
	void creaItem() { listaAsteroides->addItem(new Asteroid(game, Vector2D(0.25, 0.25))); };
};

