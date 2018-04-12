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

void StarTrekBulletsManager::shoot() { //Comprueba el estado actual de las balas (Hay alguna inactiva?)
	pair<bool, Bullets*> check = bullets_.getObjectPool();

	if (check.first) { //Si hay alguna inactiva, la activa
		check.second->setActive(true);
		check.second->setPosition(pos);
		check.second->setVelocity(vel);
	}
	else { //Si no, crea una nueva
		newShoot(check.second, vel, pos);
	}
}

void StarTrekBulletsManager::multiShoot() { //Comprueba el estado actual de las balas (Hay alguna inactiva?)
	for (int i = 0; i < 6; i++) {   
		float cosen = (float)cos(((360/6 * (i)))*M_PI/180);
		float sen = (float)sin((((360/6 * (i)))*M_PI / 180));
		
		Vector2D p;
		int x = objetoQueDispara->getPosition().getX() + objetoQueDispara->getWidth() / 2;
		int y = objetoQueDispara->getPosition().getY() + objetoQueDispara->getHeight() / 2;
		p.setX(x);
		p.setY(y);

		int vx = (p.getX()* cosen - p.getY()*sen);
		int vy = (p.getX() * sen + p.getY() * cosen);

		Vector2D dirAct = objetoQueDispara->getDirection();
		dirAct.setX(-dirAct.getX());

		Vector2D vel(vx, vy);
		vel.normalize();

		pair<bool, Bullets*> check = bullets_.getObjectPool();

		if (check.first) { //Si hay alguna inactiva, la activa
			check.second->setActive(true);
			check.second->setPosition(p);
			check.second->setVelocity(vel);
		}
		else { //Si no, crea una nueva
			newShoot(check.second,vel, p);
		}
	}
}

void StarTrekBulletsManager::update(Uint32 time) { //Esto sólo actualiza el estado de las balas
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
	//añadimos dichos metodos al Container
    bull->addPhysicsComponent(motion);
	bull->addRenderComponent(fillRect);
	//establecemos su tamaño y lo añadimos a la lista de balas
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
			pos = aux->bulletPosition_;
			vel = aux->bulletVelocity_;
			disparo();
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
	case MULTI_ON:
	{
		disparo = [this]() mutable {multiShoot(); }; //cambiamos la funcion de disparo
		break;
	}
	case MULTI_OFF:
	{
		disparo = [this]() mutable {shoot(); }; //la devolvemos a su valor original. En caso de agregar más funciones, seria cuestion de ir agregando mensajes e ir cambiando la funcion
		break;
	}
	}
}
