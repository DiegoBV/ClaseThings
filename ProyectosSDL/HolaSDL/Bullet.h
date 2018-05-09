#pragma once

#include "Container.h"


/*
 *
 */
class Bullet: public Container {
public:
	Bullet(SDLGame* game);
	virtual ~Bullet();
	void setFighterId(Uint8 id);
	Uint8 getFighterId();
	void setBulletId(Uint16 id);
	Uint16 getBulletId();
private:
	Uint8 fighterId_;
	Uint16 bulletId_;
};

