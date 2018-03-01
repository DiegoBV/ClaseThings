#pragma once
#include "Container.h"
#include "Observer.h"
#include "BasicMotionPhysics.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysics.h"
class Asteroid: public Container, public Observer
{
private:
	int contGeneraciones;
	SDL_Rect rect = { 0, 0, 50, 50 };
public:
	Asteroid();
	virtual ~Asteroid();
	Asteroid(SDLGame* game, Vector2D velocity) : Container(game), Observer()/*, contGeneraciones(randomEntre1y3)*/ { 
		this->addPhysicsComponent(new BasicMotionPhysics()); this->addRenderComponent(new ImageRenderer(getGame()->getResources()->getImageTexture(Resources::Star), rect));
			this->setVelocity(velocity); this->setWidth(50); this->setHeight(50); this->setPosition(Vector2D(getGame()->getWindowWidth() / 2, getGame()->getWindowHeight() / 2)); 
				this->addPhysicsComponent(new CircularMotionPhysics());};
	virtual void receive(Message msg) {};
};