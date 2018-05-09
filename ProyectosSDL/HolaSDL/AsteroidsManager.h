#pragma once

#include "GameObject.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
#include "RotationPhysics.h"
#include "Observer.h"
#include "SkeletonRenderer.h"
#include "Observable.h"
#include "Asteroid.h"

/*
 *
 */
class AsteroidsManager: public GameObject, public Observer, public Observable {

public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();
	virtual vector<Asteroid*>& getAsteroids();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void receive(Message* msg);
	void addNewAsteroid();
	pair<bool, Asteroid*> checkAsteroids();

private:

	vector<Asteroid*> asteroids_;


};

