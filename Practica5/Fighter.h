#pragma once
#include "Container.h"
#include "SDLGame.h"



class Fighter : public Container
{
public:
	Fighter() {}
	Fighter(SDLGame* game) : Container(game) {}
	~Fighter();
	int getId() { return id_; };
private:
	int id_;
};

