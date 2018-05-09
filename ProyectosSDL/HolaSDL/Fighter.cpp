#include "Fighter.h"

Fighter::Fighter(SDLGame* game, Uint8 id) :
		Container(game), id_(id) {

}

Fighter::~Fighter() {

}

Uint8 Fighter::getId() const {
	return id_;
}
