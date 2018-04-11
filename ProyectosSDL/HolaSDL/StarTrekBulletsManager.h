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
	bool supahBullets = false;
	bool multiSHoot = false;

	virtual void receive(Message* msg);
	

public:
	virtual void shoot(Vector2D p, Vector2D v);
	void multiShoot(Vector2D p, Vector2D v, Vector2D d, GameObject* aux);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	void newShoot(Bullets* bull, Vector2D vel, Vector2D pos);
	void roundStart();
	pair<bool, Bullets*> checkBullets();
	StarTrekBulletsManager();
	StarTrekBulletsManager(SDLGame* game) : GameObject(game) {
		//Creamos los metodos basicos de render y fisicas
		fillRect = new FillRectRenderer();
		motion = new BasicMotionPhysics();

		for (int i = 0; i < 20; i++) {
			Bullets* b = bullets_.addNewItem();
			newShoot(b, Vector2D(0.0, 0.0), Vector2D(0.0, 0.0));
		}
	}
	virtual ~StarTrekBulletsManager();
	virtual vector<Bullets*>& getBullets() { return bullets; }
};

