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
	Asteroid(SDLGame* game, Vector2D velocity, Vector2D pos) : Container(game), Observer(), contGeneraciones(5) {
		this->addPhysicsComponent(new BasicMotionPhysics()); this->addRenderComponent(new ImageRenderer(getGame()->getResources()->getImageTexture(Resources::Star), rect));
			this->setVelocity(velocity); this->setWidth(50); this->setHeight(50); this->setPosition(pos); 
				this->addPhysicsComponent(new CircularMotionPhysics());
	}
	void split();
	virtual void receive(Message msg) { if (msg.id_ == HIT) { split(); } }
	int getCont() { return contGeneraciones; }
	void setCont(int newCont) { contGeneraciones = newCont; }
};