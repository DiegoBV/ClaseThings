#pragma once
#include "Container.h"
#include "BasicMotionPhysics.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
class Asteroid: public Container
{
private:
	int contGeneraciones;
	SDL_Rect rect = { 0, 0, 50, 50 };
public:
	Asteroid(): contGeneraciones(rand() % 3 + 2) {};
	virtual ~Asteroid();
	Asteroid(SDLGame* game, Vector2D velocity, Vector2D pos) : Container(game), contGeneraciones(rand()%3 + 2) {
			this->setVelocity(velocity); this->setWidth(50); this->setHeight(50); this->setPosition(pos); 
	}
	int getCont() { return contGeneraciones; };
	void setCont(int newCont) { contGeneraciones = newCont; };
};