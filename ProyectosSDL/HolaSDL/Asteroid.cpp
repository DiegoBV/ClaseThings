#include "Asteroid.h"

Asteroid::Asteroid(SDLGame* game) :
		Container(game), id_(-1) {
}

Asteroid::~Asteroid() {
}


void Asteroid::setAsteroidId(Uint32 id) {
	id_ = id;
}

Uint8 Asteroid::getAsteroidId() {
	return id_;
}
