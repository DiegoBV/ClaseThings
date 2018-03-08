#include "CollisionManager.h"
#include "Collisions.h"
#include "messages.cpp"
void CollisionManager::update(Uint32 time) {
	vector<Bullets*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> astroids = asteroidsManager_->getAsteroidsVector();
	//Fighter* fighter = fightersManager_->getFighter();

	//comprobar colisiones entre bala y asteroide
	//comprobar colisiones entre asteroide y nave
	for (int i = 0; i < astroids.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (Collisions::collides(astroids[i], bullets[j])) {
				//this->send(AsteroidBulletCollisionMessage(BULLET_ASTEROID_COLISION, astroids[i], bullets[j]));
			}
		}
	}
	//asteroidsManager_->receive(static_cast<CollisionMessage(BULLET_ASTEROID_COLISION, astroids[0], astroids[0]));
}
