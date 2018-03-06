#pragma once
#include "Container.h"
#include "SDLGame.h"
using namespace std;

class Bullets : public Container
{
protected:
	int fighterId_;

public:
	Bullets();

	Bullets(SDLGame* game) : Container(game) {}

	~Bullets();

	void setFighterId(int id) {
		fighterId_ = id;
	}

	int getFighterId() {
		return fighterId_;
	}

};

