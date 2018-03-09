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
	int n = rand() % 2; if (n == 0) { n = -1; }
	newAst->setDirection(Vector2D(n , 0));
	newAst->setPosition(pos); // se pasaria por la constructora
	newAst->setGame(game);
	asteroides.push_back(newAst);
	asteroides[0]->setActive(false);
}

void AsteroidsManager::initAsteroides() {
	for (int i = 0; i < numAst; i++) {
		newAsteroid();
	}
}

void AsteroidsManager::updatePool() {
	pair<bool, Asteroid*> firstInactive = poolAst.getObjectPool();
	int cont = firstInactive.second->getCont();
	if (cont > 1) {
		int i = 0;
		Vector2D posInicial = Vector2D(firstInactive.second->getPosition());
		Vector2D newVel = firstInactive.second->getVelocity();
		while (i < cont) {
			pair<bool, Asteroid*> newObject = poolAst.getObjectPool();		
			newVel.rotate(i * 30);
			newObject.second->setCont(cont - 1);
			if (!newObject.first) { //se ha creado uno nuevo
				setAsteroid(newObject.second, newVel, posInicial + Vector2D(rand() % 20, rand() % 20));
				asteroides[0]->setActive(true);
			}
			else { //si no se ha creado uno nuevo, simplemente se setean sus parámetros
				newObject.second->setActive(true);
				newObject.second->setPosition(posInicial + Vector2D(rand() % 20, rand() % 20));
				newObject.second->setVelocity(newVel);
			}
			i++;
		}
	}
}

void AsteroidsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		initAsteroides(); //en vez de hacerlo en la constructora, se haria al recibir un mensaje del gameManager
		break;
	case BULLET_ASTROID_COLLISION:
		GameObject* aux = static_cast<BulletAstroidCollision*>(msg)->astroid_;
		aux->setActive(false);
		updatePool();
		break;

	};
}