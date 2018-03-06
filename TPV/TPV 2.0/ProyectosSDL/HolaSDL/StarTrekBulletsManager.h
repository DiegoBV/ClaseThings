#pragma once
#include "BulletsManager.h"
#include "GameObject.h"
#include "Fighter.h"
#include <vector>
#include "messages.h"

class StarTrekBulletsManager : public BulletsManager, public GameObject
{
protected:
	ManagerTemplate<Bullets*> bullets_;
	Bullets* getBullet();
	FillRectRenderer* fillRect;
	BasicMotionPhysics* motion;
	Vector2D basic = { 0.0, 0.0 }; //Esto es solo para pruebas, no worries

	virtual void receive(Message* msg);
	virtual void shoot(Fighter* owner, Vector2D p, Vector2D v);

public:
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	void newShoot(Bullets* bull, Vector2D vel, Vector2D pos);
	pair<bool, Bullets*> checkBullets();
	StarTrekBulletsManager();
	StarTrekBulletsManager(SDLGame* game) : GameObject(game) {
		
	}
	~StarTrekBulletsManager();
};

