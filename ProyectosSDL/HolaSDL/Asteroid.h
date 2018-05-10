#pragma once

#include "Container.h"
#include "ImageRenderer.h"
#include "BasicMotionPhysics.h"
#include "RotationPhysics.h"

/*
 *
 */
class Asteroid: public Container {
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	void setAsteroidId(Uint32 id);
	Uint8 getAsteroidId();
private:
	Uint8 id_;
};

