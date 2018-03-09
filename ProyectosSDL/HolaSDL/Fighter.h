#pragma once
#include "Container.h"
#include "SDLGame.h"
#include "Observer.h"



class Fighter : public Container, public Observer //solo por ahora, en la practica de verdad no es Observer
{
public:
	Fighter() {}
	Fighter(SDLGame* game) : Container(game) {}
	~Fighter();
	virtual void receive(Message* msg) {}
	int getId() { return id_; };
private:
	int id_;
};

