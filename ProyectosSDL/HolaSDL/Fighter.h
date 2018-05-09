#pragma once

#include "Container.h"

/*
 *
 */
class Fighter: public Container {
public:
	Fighter(SDLGame* game, Uint8 id);
	virtual ~Fighter();
	Uint8 getId() const;
private:
	Uint8 id_;
};

