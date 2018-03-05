#include "BulletsManager.h"
#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"
#include "ExampleGame.h"

BulletsManager::~BulletsManager()
{
}

void BulletsManager::shoot(Vector2D p, Vector2D v) { //Comprueba el estado actual de las balas (Hay alguna inactiva?)
	pair<bool, Container*> check = checkBullets();

	if (check.first) { //Si hay alguna inactiva, la activa
		check.second->setActive(true);
		check.second->setPosition(p);
		check.second->setVelocity(v);
	}
	else { //Si no, crea una nueva
		newShoot(v, p);
	}	
}

void BulletsManager::update(Uint32 time) { //Esto sólo actualiza el estado de las balas
	for (int i = 0; i < bullets.size(); i++) {
		if ((*bullets.getItem(i))->isActive()) {
			static_cast<Container*>(*bullets.getItem(i))->update(time);
		}
	}
}

pair<bool, Container*> BulletsManager::checkBullets() {
	Uint32 i = 0;
	bool encontrado = false;
	Container* aux;
	while (i < bullets.size()) {
		if (!(*bullets.getItem(i))->isActive()) {
			encontrado = true;
			aux = (*bullets.getItem(i));
		}
		i++;
	}
	pair<bool, Container*> resultado(encontrado, aux);
	return resultado;
}

void BulletsManager::render(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++) {
		static_cast<Container*>(*bullets.getItem(i))->render(time);
	}
}

void BulletsManager::newShoot(Vector2D vel, Vector2D pos) {
	//Creamos el nuevo game component
	Container* newBullet = new Container(this->getGame());

	//Creamos los metodos basicos de render y fisicas
	FillRectRenderer* fillRect = new FillRectRenderer();
	BasicMotionPhysics* motion = new BasicMotionPhysics();

	//añadimos dichos metodos al Container
	newBullet->addPhysicsComponent(motion);
	newBullet->addRenderComponent(fillRect);

	//establecemos su tamaño y lo añadimos a la lista de balas
	newBullet->setHeight(5);
	newBullet->setWidth(5);
	newBullet->setVelocity(vel);
	newBullet->setPosition(pos);
	bullets.addNewItem(newBullet);
	static_cast<ExampleGame*>(game)->pushObject(newBullet);
}