#pragma once
#include "BulletsManager.h"

class StarWarsBulletsManager: public GameObject, public BulletsManager
{
private:
	std::vector<GameObject*> bullets;
public:
	StarWarsBulletsManager(SDLGame* game) : GameObject(game) {};
	virtual ~StarWarsBulletsManager();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void shoot(GameObject* o, Vector2D p, Vector2D v);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};

};

