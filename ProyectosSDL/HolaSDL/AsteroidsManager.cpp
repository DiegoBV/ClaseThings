#include "AsteroidsManager.h"
#include "ExampleGame.h"
#include <algorithm>

AsteroidsManager::AsteroidsManager()
{
}


AsteroidsManager::~AsteroidsManager()
{
	if (astroidImage_ != nullptr) { delete astroidImage_; astroidImage_ = nullptr; }

	if (circularPhysics_ != nullptr) { delete circularPhysics_; circularPhysics_ = nullptr; }

	if (basicMotionPhysics_ != nullptr) { delete basicMotionPhysics_; basicMotionPhysics_ = nullptr; }

	if (rotationPhysics_ != nullptr) { delete rotationPhysics_; rotationPhysics_ = nullptr; }
}

AsteroidsManager::AsteroidsManager(SDLGame* game) : game(game) {
	 astroidImage_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Astroid), rect); 
	 circularPhysics_ = new CircularMotionPhysics();
	 basicMotionPhysics_ = new BasicMotionPhysics();
	 rotationPhysics_ = new RotationPhysics();
	 centro = { game->getWindowWidth()/2 - 200, game->getWindowHeight()/2 - 200, 400, 400 }; //centro de la pantalla
	 numAst = initAsts = numAstIniciales;
	 initAsteroides();
}

void AsteroidsManager::newAsteroid() { //crea los primeros asteroides
	Asteroid* newAst = poolAst.addNewItem();
	double u = (double)rand() / (RAND_MAX + 1)*(1 - 0.1) + 0.1;
	Vector2D vel(u, u);
	setAsteroid(newAst, vel, Vector2D(generatePos()));
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
			asteroides[i]->setPosition(generatePos());
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
	if (numAst == 0) { send(&Message(NO_MORE_ATROIDS)); }
}

void AsteroidsManager::receive(Message* msg) {
	switch (msg->id_) {
	case ROUND_START:
		for (unsigned int i = 0; i < asteroides.size(); i++) {
			asteroides[i]->setActive(false);
		}
		initAsteroides();
		break;
	case ROUND_OVER:
   		numAst = numAstIniciales;
		break;
	case BULLET_ASTROID_COLLISION:
		GameObject* aux = static_cast<BulletAstroidCollision*>(msg)->astroid_;
		aux->setActive(false);
		numAst--; //reduce el numero de asteroides
		updatePool();
		break;
	};
}

Vector2D AsteroidsManager::generatePos(){//genera posicion random en los bordes de la poantalla
	SDL_Point p{ rand() % game->getWindowWidth(), rand() % game->getWindowHeight() };
	while (SDL_PointInRect(&p, &centro)) { p.x = rand() % game->getWindowWidth(); p.y = rand() % game->getWindowHeight(); };
	return Vector2D(p.x, p.y);
}