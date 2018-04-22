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
	
	virtual void update(Uint32 time) {
		if (this->getPosition().getX() > this->getGame()->getWindowWidth() || this->getPosition().getY() > this->getGame()->getWindowHeight() || this->getPosition().getX() < 0 || this->getPosition().getY() < 0) {
        		this->setActive(false);
		}
		Container::update(time);
	}

	int getFighterId() {
		return fighterId_;
	}

};

