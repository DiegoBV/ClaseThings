#include "CollisionManager.h"
#include "Collisions.h"

CollisionManager::CollisionManager(SDLGame* game,
		BulletsManager* bulletsManager, FightersManager* fightersManager,
		AsteroidsManager* asteroidsManager) :
		GameObject(game), bulletsManager_(bulletsManager), fightersManager_(
				fightersManager), asteroidsManager_(asteroidsManager) {
}

CollisionManager::~CollisionManager() {
}

void CollisionManager::handleInput(Uint32 time, const SDL_Event& event) {
}

void CollisionManager::update(Uint32 time) {

	// only the master client checks collisions
	if (!getGame()->isMasterClient())
		return;

	vector<vector<Bullet*>> bullets = bulletsManager_->getBullets();
	vector<Fighter*> fighters = fightersManager_->getFighters();
	vector<Asteroid*> asteroids = asteroidsManager_->getAsteroids();

	for (vector<Bullet*>& fighterBullets_ : bullets) {
		for (Bullet* b : fighterBullets_) {
			if (b->isActive()) {
				for (Fighter* f : fighters) {
					if (f != nullptr && f->isActive()
							&& Collisions::collidesWithRotation(b, f)) {
						BulletFighterCollisionMsg m = { f->getId(),
								b->getBulletId(), b->getFighterId() };
						send(&m);
						break; // it can kill only one fighter
					}
				}

				Uint8 i = 0;
				for (Asteroid* a : asteroids) {
					if (a != nullptr && a->isActive() && Collisions::collidesWithRotation(a, b)) { //FOR DE COLISIONES ENTRE ASTEROIDES Y BALAS
						BulletAsteroidCollisionMsg m = { b->getBulletId(), b->getFighterId(), i };
						send(&m);
					}
					i++;
				}
			}
		}
	}

	/*for (Asteroid* a : asteroids) { //FOR DE COLISIONES ENTRE ASTEROIDES Y FIGHTERS
		if (a->isActive()) {
			for (Fighter* f : fighters) {
				if (f != nullptr && f->isActive() && Collisions::collidesWithRotation(a, f)) {
					AsteroidFighterCollision m = AsteroidFighterCollision(f->getId());
					send(&m);
				}
			}
		}
	}*/
}

void CollisionManager::render(Uint32 time) {
}
