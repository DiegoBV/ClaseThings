#pragma once
#include "GameObject.h"
#include "ManagerTemplate.h"
#include "Observable.h"
#include "Container.h"

class BulletsManager : public GameObject
{
protected:
	ManagerTemplate<Container*> bullets;
	SDLGame* game;
	Vector2D basic = {0.0, 0.0};
public:
	BulletsManager(SDLGame* game) : GameObject(game) {
	};
	virtual ~BulletsManager();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void shoot(Vector2D p, Vector2D v);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	void newShoot(Vector2D vel, Vector2D pos);
	pair<bool, Container*> checkBullets();
};

