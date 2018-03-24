#include "CollisionManager.h"
#include "Collisions.h"

CollisionManager::CollisionManager() {
}
void CollisionManager::update(Uint32 time) {
	vector<Bullets*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> astroids = asteroidsManager_->getAsteroidsVector();
	Fighter* fighter = fightersManager_->getFighter();

	//comprobar colisiones entre asteroide y nave
	for (int i = 0; i < astroids.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (Collisions::collidesWithRotation(astroids[i], bullets[j]) && astroids[i]->isActive() && bullets[j]->isActive()) {
				this->send(&BulletAstroidCollision(bullets[j], astroids[i]));
			}
		}
		if (Collisions::collidesWithRotation(astroids[i], fighter) && astroids[i]->isActive() && fighter->isActive()) {
			this->send(&AstroidFighterCollision(astroids[i], fighter));
		}
	}
	//asteroidsManager_->receive(static_cast<CollisionMessage(BULLET_ASTEROID_COLISION, astroids[0], astroids[0]));
}
