#include "AsteroidsManager.h"

#include "Collisions.h"

AsteroidsManager::AsteroidsManager(SDLGame* game) :
		GameObject(game) {
}

AsteroidsManager::~AsteroidsManager() {
}

vector<Asteroid*>& AsteroidsManager::getAsteroids() {
	return asteroids_;
}

void AsteroidsManager::handleInput(Uint32 time, const SDL_Event& event) {
}

void AsteroidsManager::update(Uint32 time) {
	for (Asteroid* a : asteroids_)
		if (a->isActive()) {
			a->update(time);
		}
}

void AsteroidsManager::render(Uint32 time) {
	for (Asteroid* a : asteroids_)
		if (a->isActive()) {
			a->render(time);
		}
}

void AsteroidsManager::receive(Message* msg) {
	switch (msg->mType_) {
	case GAME_START:
		// add you code
		break;
	case ADD_ASTEROID:
		this->addNewAsteroid();
		break;
		//add other cases
	}
}

void AsteroidsManager::addNewAsteroid(){

	Vector2D vel((1 - 2 * (rand() % 2))*((rand() % 10) + 1), ((rand() % 10) + 1));
	vel.normalize();
	vel = vel * 0.5;
	Vector2D pos(rand() % getGame()->getWindowWidth(), rand() % 30);
	Vector2D dir(0, -1);
	int width = (rand() % 10) + 20;
	int height = (rand() % 10) + 20;

	pair<bool, Asteroid*> par = checkAsteroids();

	Asteroid* ast = nullptr;

	if (par.first){
		ast = par.second;
	}
	else{
		ast = new Asteroid(game_);

	}

	if (ast != nullptr){
		ast->setVelocity(vel);
		ast->setPosition(pos);
		ast->setDirection(dir);
		ast->setWidth(width);
		ast->setHeight(height);
		ast->setActive(true);
	}
}

pair<bool, Asteroid*> AsteroidsManager::checkAsteroids() {
	Uint32 i = 0;
	bool encontrado = false;
	Asteroid* aux;
	while (i < asteroids_.size()) {
		if (!asteroids_[i]->isActive()) {
			encontrado = true;
			aux = (asteroids_[i]);
		}
		i++;
	}

	pair<bool, Asteroid*> resultado(encontrado, aux);
	return resultado;
}

