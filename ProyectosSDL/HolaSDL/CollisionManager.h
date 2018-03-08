#pragma once
#include "Observable.h"
#include "GameObject.h"
#include "BulletsManager.h"
#include "AsteroidsManager.h"

class CollisionManager: public GameObject, public Observable //añadiria a su lista de observers manager de ast y balas y el fighter para mandarles el mensaje de que han chocado
{
public:
	CollisionManager() {};
	~CollisionManager() {};
	CollisionManager(SDLGame* game, BulletsManager* bulletsManager, AsteroidsManager* astroidManager/*, FightersManager* fightersManager*/):GameObject(game), 
		bulletsManager_(bulletsManager), asteroidsManager_(astroidManager) {
			this->registerObserver(asteroidsManager_); this->registerObserver(bulletsManager_); }; //recibe punteros para acceder a las balas, asteroides, nave...
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};
private:
	BulletsManager* bulletsManager_;
	AsteroidsManager* asteroidsManager_;
	//FightersManager* fightersManager_;

};

