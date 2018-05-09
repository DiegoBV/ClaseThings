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
	virtual void update(Uint32 time) {
		if (this->getPosition().getX() > this->getGame()->getWindowWidth() || this->getPosition().getY() > this->getGame()->getWindowHeight() || this->getPosition().getX() < 0 || this->getPosition().getY() < 0) { //maybe componente (?)
			this->setActive(false);
		}
		Container::update(time);
	}

private:
	Uint8 id_;
};

