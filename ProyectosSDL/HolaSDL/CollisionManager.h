#pragma once
#include "Observable.h"
#include "BulletsManager.h"
#include "AsteroidsManager.h"
#include "SoundManager.h"
#include "FightersManager.h"

class CollisionManager: public GameObject, public Observable //añadiria a su lista de observers manager de ast y balas y el fighter para mandarles el mensaje de que han chocado
{
private:
	BulletsManager* bulletsManager_;
	AsteroidsManager* asteroidsManager_;
	FightersManager* fightersManager_;
	SoundManager* soundManager_;

public:
	CollisionManager();
	virtual ~CollisionManager() {}
	CollisionManager(SDLGame* game, BulletsManager* bulletsManager, AsteroidsManager* astroidManager, FightersManager* fightersManager, SoundManager* soundManager):GameObject(game), 
		bulletsManager_(bulletsManager), asteroidsManager_(astroidManager), fightersManager_(fightersManager), soundManager_(soundManager) {
		this->registerObserver(asteroidsManager_); 
		this->registerObserver(bulletsManager_); 
		this->registerObserver(soundManager_);
	}; //recibe punteros para acceder a las balas, asteroides, nave...
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};
};

