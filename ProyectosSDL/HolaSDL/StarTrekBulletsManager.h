#pragma once
#include "BulletsManager.h"
#include <vector>
#include "Fighter.h"
#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"

class StarTrekBulletsManager : public BulletsManager, public GameObject
{
protected:
	ManagerTemplate<Bullets> bullets_;
	vector<Bullets*> bullets;
	Bullets* getBullet(int i);
	FillRectRenderer* fillRect;
	BasicMotionPhysics* motion;
	Vector2D basic = { 0.0, 0.0 }; //Esto es solo para pruebas, no worries

	virtual void receive(Message* msg);
	

public:
	virtual void shoot(Fighter* owner, Vector2D p, Vector2D v);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	void newShoot(Bullets* bull, Vector2D vel, Vector2D pos);
	void roundStart();
	pair<bool, Bullets*> checkBullets();
	StarTrekBulletsManager();
	StarTrekBulletsManager(SDLGame* game) : GameObject(game) {
		Bullets* b = new Bullets(game_);
		bullets_.pushSomething(b);
		bullets.push_back(b);
	}
	~StarTrekBulletsManager();
	virtual vector<Bullets*>& getBullets() { return bullets; }
};

