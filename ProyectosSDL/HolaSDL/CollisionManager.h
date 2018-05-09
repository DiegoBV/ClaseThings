#pragma once

#include "AsteroidsManager.h"
#include "BulletsManager.h"
#include "Fighter.h"
#include "Observable.h"
#include "FightersManager.h"

/*
 *
 */
class CollisionManager: public GameObject, public Observable {
public:
	CollisionManager(SDLGame* game, BulletsManager* bulletsManager,
			FightersManager* fightersManager, AsteroidsManager* asteroidsManager);
	virtual ~CollisionManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
private:
	BulletsManager* bulletsManager_;
	FightersManager* fightersManager_;
	AsteroidsManager* asteroidsManager_;
};

