#include "AsteroidsManager.h"
#include "ExampleGame.h"
#include <algorithm>

AsteroidsManager::AsteroidsManager()
{
}


AsteroidsManager::~AsteroidsManager()
{
	if (astroidImage_ != nullptr)
		delete astroidImage_;
	if (circularPhysics_ != nullptr)
		delete circularPhysics_;
	if (basicMotionPhysics_ != nullptr)
		delete basicMotionPhysics_;
	if (rotationPhysics_ != nullptr)
		delete rotationPhysics_;
}

AsteroidsManager::AsteroidsManager(SDLGame* game) : game(game) {
	 astroidImage_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Astroid), rect); 
	 circularPhysics_ = new CircularMotionPhysics();
	 basicMotionPhysics_ = new BasicMotionPhysics();
	 rotationPhysics_ = new RotationPhysics();  
	 numAst = initAsts = 3;
	 initAsteroides();
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
	newAst->setHeight(30);
	newAst->setWidth(30);
	newAst->setVelocity(vel);
	int n = rand() % 2; if (n == 0) { n = -1; }
	newAst->setDirection(Vector2D(n , 0));
	newAst->setPosition(pos); // se pasaria por la constructora
	newAst->setGame(game);
	asteroides.push_back(newAst);
}

void AsteroidsManager::initAsteroides() {
	if (asteroides.size() <= 0) {
		for (int i = 0; i < initAsts; i++) {
			newAsteroid();
		}
	}
	else {
		for (int i = 0; i < initAsts; i++) {
			asteroides[i]->setActive(true);
			asteroides[i]->setPosition(Vector2D(rand() % game->getWindowWidth(), rand() % game->getWindowHeight())); //cambiar direccion tambien y tal
			asteroides[i]->setCont(rand() % 3 + 2);
		}
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
				setAsteroid(newObject.second, newVel, posInicial);
				asteroides[0]->setActive(true);
			}
			else { //si no se ha creado uno nuevo, simplemente se setean sus parámetros
				newObject.second->setActive(true);
				newObject.second->setPosition(posInicial);
				newObject.second->setVelocity(newVel);
			}
			numAst++;
			i++;
		}
	}
}

void AsteroidsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		for (unsigned int i = 0; i < asteroides.size(); i++) {
			asteroides[i]->setActive(false);
		}
		initAsteroides();
		break;
	case ROUND_OVER: //(?)
		break;
	case BULLET_ASTROID_COLLISION:
		GameObject* aux = static_cast<BulletAstroidCollision*>(msg)->astroid_;
		aux->setActive(false);
		numAst--; //reduce el numero de asteroides
		if (numAst == 0) { send(&Message(NO_MORE_ATROIDS)); }
		updatePool();
		break;
	};
}