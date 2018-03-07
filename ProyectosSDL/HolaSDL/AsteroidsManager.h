#pragma once
#include "ManagerTemplate.h"
#include "Asteroid.h"
#include "Observable.h"
class AsteroidsManager: public Observable, public Observer
{
private:
	SDL_Rect rect = { 0, 0, 50, 50 };
	ManagerTemplate<Asteroid> poolAst; //cambiar GO x gameObject
	vector <Asteroid*> asteroides;
	void initAsteroides();
	void newAsteroid();
	void setAsteroid(Asteroid* newAst, Vector2D vel, Vector2D pos);
	SDLGame* game;
	ImageRenderer* astroidImage_;
	CircularMotionPhysics* circularPhysics_;
	BasicMotionPhysics* basicMotionPhysics_;
	//RotationPhysics rotationPhysics_;
	int numAst;
public:
	AsteroidsManager();
	~AsteroidsManager();
	AsteroidsManager(SDLGame* game);
	void updatePool();
	virtual void receive(Message msg) {}
};

