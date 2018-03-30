#pragma once
#include "Container.h"
#include "Observer.h"
class BadgeObject :
	public Container, public Observer
{
private:
	ImageRenderer rend;
	bool renderAdd = false;
	SDL_Rect rect = { 0, 0, 400, 300 };
public:
	BadgeObject();
	BadgeObject(SDLGame* game);
	virtual ~BadgeObject();
	virtual void receive(Message* msg);
};

