#include "AsteroidsManager.h"
#include "ExampleGame.h"
#include <algorithm>

AsteroidsManager::AsteroidsManager()
{
}


AsteroidsManager::~AsteroidsManager()
{
}

AsteroidsManager::AsteroidsManager(SDLGame* game) : game(game) {
	 astroidImage_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Star), rect); circularPhysics_ = new CircularMotionPhysics();
	 basicMotionPhysics_ = new BasicMotionPhysics(); rotationPhysics_ = new RotationPhysics(); numAst = 2; initAsteroides();
}

void AsteroidsManager::newAsteroid() { //crea los primeros asteroides
	Asteroid* newAst = poolAst.addNewItem();
	newAst->setCont(5);
	double u = (double)rand() / (RAND_MAX + 1)*(1 - 0.1) + 0.1;
	Vector2D vel(u, u);
	setAsteroid(newAst, vel, Vector2D(rand() % game->getWindowWidth(), rand() % game->getWindowHeight()));
}

void AsteroidsManager::setAsteroid(Asteroid* newAst, Vector2D vel, Vector2D pos) { //Setea los parámetros de un asteroide
	newAst->addPhysicsComponent(circularPhysics_);
	newAst->addPhysicsComponent(basicMotionPhysics_);
	newAst->addPhysicsComponent(rotationPhysics_);
	newAst->addRenderComponent(astroidImage_);
	newAst->setActive(true);
	newAst->setHeight(50);
	newAst->setWidth(50);
	newAst->setVelocity(vel);
	newAst->setDirection(Vector2D(1, 0));
	newAst->setPosition(pos); // se pasaria por la constructora
	newAst->setGame(game);
	asteroides.push_back(newAst);
	asteroides[0]->setActive(false);
	poolAst.pushSomething(newAst);
	static_cast<ExampleGame*>(game)->pushObject(newAst);
}

void AsteroidsManager::initAsteroides() {
	for (int i = 0; i < numAst; i++) {
		newAsteroid();
	}
}

void AsteroidsManager::updatePool() {
	pair<bool, Asteroid*> firstInactive = poolAst.getObjectPool();
	int cont = firstInactive.second->getCont();
	int i = 0;
	Vector2D posInicial = Vector2D(firstInactive.second->getPosition());
	while (i < cont) {
		pair<bool, Asteroid*> newObject = poolAst.getObjectPool();
		if (!newObject.first) { //se ha creado uno nuevo
			setAsteroid(newObject.second, Vector2D(0.2, 0.2), posInicial + Vector2D(rand()%20, rand()%20));
		}
		newObject.second->setCont(firstInactive.second->getCont() - 1);
		i++;
	}
}

void AsteroidsManager::receive(Message msg) {
	switch (msg.id_) {
	case BULLET_ASTEROID_COLISION:
		break;
	case ROUND_START:
		initAsteroides(); //en vez de hacerlo en la constructora, se haria al recibir un mensaje del gameManager
		break;
	};
}