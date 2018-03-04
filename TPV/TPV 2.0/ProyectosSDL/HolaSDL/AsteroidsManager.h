#pragma once
#include "ManagerTemplate.h"
#include "Asteroid.h"
#include "Observable.h"
class AsteroidsManager: public Observable //maybe ser observable no se requiere y es mejor ser observador--> que cada asteroide le diga ehhh que mahn dao loko
{
private:
	ManagerTemplate<Asteroid*> listaAsteroides; //cambiar GO x gameObject, no sé si se hereda o se incluye la template
	SDLGame* game;
public:
	AsteroidsManager();
	~AsteroidsManager();
	AsteroidsManager(SDLGame* game, vector<Asteroid*> asteroides);
	void updatePool();
	void kk() { send(HIT); }
};

