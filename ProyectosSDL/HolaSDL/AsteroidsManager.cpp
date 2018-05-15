#include "AsteroidsManager.h"

#include "Collisions.h"

AsteroidsManager::AsteroidsManager(SDLGame* game) :
		GameObject(game) {

	render_ = ImageRenderer(game->getResources()->getImageTexture(Resources::Astroid));

	rot_ = RotationPhysics(1);
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
		if (getGame()->isMasterClient()) {
			this->addNewAsteroid(false);
			send(&NewAsteroidMsg(ASTEROID_ADDED, getLastAsteroid()->getPosition(), getLastAsteroid()->getVelocity(), getLastAsteroid()->getDirection(), getLastAsteroid()->getWidth(), getLastAsteroid()->getHeight(), getLastAsteroid()->isActive()));
			cout << "mandando info a otros players";
		}
		break;
	case ASTEROID_ADDED:
		cout << "recibiendo info..."; //SE RECIBE MAL
		NewAsteroidMsg* m = static_cast<NewAsteroidMsg*>(msg);
		//cout << endl << m->astPosition_ << "+ " << m->astVelocity_ << "+ " << m->astDirection_ << "+ " << m->astWidth_ << "+ " << m->astHeight_ << "+ " << m->astActive_ << endl;
		this->msg = m;
		this->addNewAsteroid(true);
		break;
		//add other cases
	}
}

void AsteroidsManager::addNewAsteroid(bool updating){


	pair<bool, Asteroid*> par = checkAsteroids();

	Asteroid* ast = nullptr;

	if (par.first){
		ast = par.second;
	}
	else{
		ast = new Asteroid(game_);
		ast->addRenderComponent(&render_);
		ast->addPhysicsComponent(&mov_);
		ast->addPhysicsComponent(&rot_);
	}

	if (ast != nullptr){
		if (!updating) setRandomParam(ast);  //updating es un bool que indica si es el primero en crearse o esta updateando el juego
		else { setParam(msg->astPosition_, msg->astVelocity_, msg->astDirection_, msg->astWidth_, msg->astHeight_, msg->astActive_, ast); /*cout << msg->astPosition_ << "+ " << msg->astVelocity_ << "+ " << msg->astDirection_ << "+ " << msg->astWidth_ << "+ " << msg->astHeight_ << "+ " << msg->astActive_;*/ }
		asteroids_.push_back(ast);
	}

	cout << asteroids_.size();
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

void AsteroidsManager::setRandomParam(Asteroid* ast)
{
	Vector2D vel((1 - 2 * (rand() % 2))*((rand() % 10) + 1), ((rand() % 10) + 1));
	vel.normalize();
	vel = vel * 0.5;
	Vector2D pos(rand() % getGame()->getWindowWidth(), rand() % 30);
	Vector2D dir(0, -1);
	int width = (rand() % 10) + 20;
	int height = (rand() % 10) + 20;

	setParam(pos, vel, dir, width, height, true, ast);
}

void AsteroidsManager::setParam(Vector2D pos, Vector2D vel, Vector2D dir, int width, int height, bool active, Asteroid* ast)
{
	ast->setVelocity(vel);
	ast->setPosition(pos);
	ast->setDirection(dir);
	ast->setWidth(width);
	ast->setHeight(height);
	ast->setActive(true);
}

