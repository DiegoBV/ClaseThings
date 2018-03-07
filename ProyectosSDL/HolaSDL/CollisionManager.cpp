#include "CollisionManager.h"
void CollisionManager::update(Uint32 time) {
	//vector<Bullet*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> astroids = asteroidsManager_->getAsteroidsVector();
	//Fighter* fighter = fightersManager_->getFighter();

	//comprobar colisiones entre bala y asteroide
	//comprobar colisiones entre asteroide y nave
	asteroidsManager_->receive(CollisionMessage(BULLET_ASTEROID_COLISION, astroids[0], astroids[0]));
}
