#include "StarTrekBulletsManager.h"
#include "BasicMotionPhysics.h"
#include "ExampleGame.h"

StarTrekBulletsManager::StarTrekBulletsManager()
{
}


StarTrekBulletsManager::~StarTrekBulletsManager()
{
	if (fillRect != nullptr)
		delete fillRect;
	if (motion != nullptr)
		delete motion;
}

void StarTrekBulletsManager::shoot(vector<Vector2D> pos, vector<Vector2D> vels) { //Comprueba el estado actual de las balas (Hay alguna inactiva?)
	for (unsigned int i = 0; i < pos.size(); i++) {
		pair<bool, Bullets*> check = bullets_.getObjectPool();

		if (check.first) { //Si hay alguna inactiva, la activa
			check.second->setActive(true);
			check.second->setPosition(pos[i]);
			check.second->setVelocity(vels[i]);
		}
		else { //Si no, crea una nueva
			newShoot(check.second, vels[i], pos[i]);
		}
	}
}

void StarTrekBulletsManager::update(Uint32 time) { //Esto s�lo actualiza el estado de las balas
	for (int i = 0; i < bullets_.size(); i++) {
		bullets_.getItem(i)->update(time);
	}
}

pair<bool, Bullets*> StarTrekBulletsManager::checkBullets() {
	Uint32 i = 0;
	bool encontrado = false;
	Bullets* aux;
	while (i < bullets_.size()) {
		if (!(bullets_.getItem(i))->isActive()) {
			encontrado = true;
			aux = (bullets_.getItem(i));
		}
		i++;
	}
	pair<bool, Bullets*> resultado(encontrado, aux);
	return resultado;
}

void StarTrekBulletsManager::render(Uint32 time) {
	for (int i = 0; i < bullets_.size(); i++) {
		bullets_.getItem(i)->render(time);
	}
}

void StarTrekBulletsManager::newShoot(Bullets* bull, Vector2D vel, Vector2D pos) {
	//a�adimos dichos metodos al Container
    bull->addPhysicsComponent(motion);
	bull->addRenderComponent(fillRect);
	//establecemos su tama�o y lo a�adimos a la lista de balas
	bull->setHeight(2);
	bull->setWidth(2);
	bull->setVelocity(vel);
	bull->setPosition(pos);
	bull->setGame(game_);
	bullets.push_back(bull);
}

void StarTrekBulletsManager::roundStart() {
	for (int i = 0; i < bullets_.size(); i++) {
		if ((bullets_.getItem(i))->isActive()) {
			(bullets_.getItem(i))->setActive(false);
		}
	}
}

Bullets * StarTrekBulletsManager::getBullet(int i)
{
	return bullets_.getItem(i);
}

void StarTrekBulletsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		roundStart();
		break;
	case ROUND_OVER:
		roundStart();
		break;
	case BULLET_ASTROID_COLLISION:
		if (!supahBullets)
			static_cast<BulletAstroidCollision*>(msg)->bullet_->setActive(false);
		break;
	case BULLET_FIGHTER_COLLISION:
		//static_cast<FighterBulletCollisionMessage*>(msg)->o2_->setActive(false);
		break;
	case FIGHTER_SHOOT:
	{	FighterIsShooting* aux = static_cast<FighterIsShooting*>(msg);
	if (aux != nullptr && aux->fighter_ != nullptr) {
		objetoQueDispara = aux->fighter_;
		shoot(aux->bulletPosition_, aux->bulletVelocity_);
	}
	break;
	}
	case SUPAH_ON:
	{
		supahBullets = true;
		break;
	}
	case SUPAH_OFF:
	{
		supahBullets = false;
		break;
	}
	}
}
