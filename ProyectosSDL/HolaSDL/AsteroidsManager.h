#pragma once
#include "ManagerTemplate.h"
#include "Asteroid.h"
#include "Observable.h"
#include "RotationPhysics.h"
class AsteroidsManager: public GameObject, public Observable, public Observer
{
private:
	SDL_Rect rect = { 0, 0, 151, 143 };
	ManagerTemplate<Asteroid> poolAst; //cambiar GO x gameObject
	vector <Asteroid*> asteroides;
	void initAsteroides();
	void newAsteroid();
	void setAsteroid(Asteroid* newAst, Vector2D vel, Vector2D pos);
	SDLGame* game;
	ImageRenderer* astroidImage_;
	CircularMotionPhysics* circularPhysics_;
	BasicMotionPhysics* basicMotionPhysics_;
	RotationPhysics* rotationPhysics_;
	int numAst;
	int initAsts; 
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time) { for (Asteroid* it : asteroides) { it->update(time); } };
	virtual void render(Uint32 time) { for (Asteroid* it : asteroides) { it->render(time); } };
public:
	AsteroidsManager();
	~AsteroidsManager();
	AsteroidsManager(SDLGame* game);
	void updatePool();
	virtual void receive(Message* msg);
	vector <Asteroid*> getAsteroidsVector() { return asteroides; }
};

