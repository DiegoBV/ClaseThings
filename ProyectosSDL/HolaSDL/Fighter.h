#pragma once
#include "Container.h"
#include "SDLGame.h"
#include "Observer.h"



class Fighter : public Container, public Observer
{
public:
	Fighter(SDLGame* game) : Container(game) {}
	~Fighter();
	virtual void receive(Message* msg) {}
};

