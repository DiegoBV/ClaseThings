#include "Bullet.h"

Bullet::Bullet(SDLGame* game) :
		Container(game), fighterId_(0), bulletId_(0) {
}

Bullet::~Bullet() {
}

void Bullet::setFighterId(Uint8 id) {
	fighterId_ = id;
}

Uint8 Bullet::getFighterId() {
	return fighterId_;
}

void Bullet::setBulletId(Uint16 id) {
	bulletId_ = id;
}

Uint16 Bullet::getBulletId() {
	return bulletId_;
}
