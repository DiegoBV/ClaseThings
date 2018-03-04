#pragma once
#include "ManagerTemplate.h"
#include "Asteroid.h"
#include "Observable.h"
class AsteroidsManager: public Observable //maybe ser observable no se requiere y es mejor ser observador--> que cada asteroide le diga ehhh que mahn dao loko
{
private:
	ManagerTemplate<Asteroid*> listaAsteroides; //cambiar GO x gameObject
	SDLGame* game;
public:
	AsteroidsManager();
	~AsteroidsManager();
	AsteroidsManager(SDLGame* game, vector<Asteroid*> asteroides);
	void updatePool();
	pair<bool, vector<Asteroid*>> renovarPool();
	void creaItem(Vector2D vel, Vector2D pos, int newCont);
	void kk() { send(HIT); }
};

