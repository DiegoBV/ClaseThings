#include "FightersManager.h"
#include "Fighter.h"
#include "NetworkMessenger.h"

FightersManager::FightersManager(SDLGame* game, NetworkMessenger* nm,
		BulletsManager* bm) :
		GameObject(game), //
		fighters_(), //
		freeMove_(SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, 2, 5), //
		circularMotionPhysics_(), //
		fighterImage_(
				game->getResources()->getImageTexture(Resources::Airplanes), {
						47, 90, 207, 250 }), skeletonRendered_(), gun_(
				SDLK_SPACE, 3000, 6) {

	freeMove_.registerObserver(nm);
	gun_.registerObserver(bm);
	gun_.registerObserver(nm);
}

void FightersManager::init() {
}

FightersManager::~FightersManager() {
}

void FightersManager::handleInput(Uint32 time, const SDL_Event& event) {
	for (Fighter* f : fighters_)
		if (f != nullptr && f->isActive())
			f->handleInput(time, event);
}

void FightersManager::update(Uint32 time) {
	for (Fighter* f : fighters_)
		if (f != nullptr && f->isActive())
			f->update(time);
}

void FightersManager::render(Uint32 time) {
	for (Fighter* f : fighters_)
		if (f != nullptr && f->isActive())
			f->render(time);
}

void FightersManager::receive(Message* msg) {
	switch (msg->mType_) {
	case PLAYER_INFO:
		initFighter(static_cast<PlayerInfoMsg*>(msg)->clientId_);
		break;
	case GAME_START:
		startGame();
		break;
	case GAME_OVER:
		endGame();
		break;
	case FIGHETR_STATE:
		updateFighterState(static_cast<FighterStateMsg*>(msg));
		break;
	case BULLET_FIGHTER_COLLISION:
		killPlayer(static_cast<BulletFighterCollisionMsg*>(msg)->fighterId_);
		break;
	case FIGHTER_ASTEROID_COLLISION:
		killPlayer(static_cast<AsteroidFighterCollision*>(msg)->fighterId_);
		break;
	case DISCONNECTED:
		disableFighters();
		break;
	}
}

vector<Fighter*>& FightersManager::getFighters() {
	return fighters_;
}

void FightersManager::initFighter(Uint8 id) {
	if (fighters_.size() <= id) {
		fighters_.resize(id + 1);
	}
	if (fighters_[id] == nullptr) {
		fighters_[id] = new Fighter(getGame(), id);
		fighters_[id]->addRenderComponent(&fighterImage_);
		fighters_[id]->addPhysicsComponent(&circularMotionPhysics_);
		fighters_[id]->setActive(false);
		if (id == getGame()->getClientId()) {
			fighters_[id]->addInputComponent(&freeMove_);
			fighters_[id]->addInputComponent(&gun_);
			fighters_[id]->addRenderComponent(&skeletonRendered_);
		}
	}
}

void FightersManager::startGame() {

	// choose an initial setting for the local player and send it over

	Fighter* f = fighters_[getGame()->getClientId()];

	f->setPosition(
			Vector2D(rand() % getGame()->getWindowWidth(),
					rand() % getGame()->getWindowHeight()));
	f->setWidth(50);
	f->setHeight(50);
	f->setVelocity( Vector2D(0,0));
	f->setDirection( Vector2D(0,-1));

	enableFighters();

	sendPlayerState();
}

void FightersManager::sendPlayerState() {
	Fighter* f = fighters_[getGame()->getClientId()];
	FighterStateMsg msg = { //
			f->getId(), //
			f->getPosition(), //
			f->getDirection(), //
			f->getVelocity(), //
			f->getWidth(), //
			f->getHeight() //
	};
	send(&msg);
}

void FightersManager::updateFighterState(FighterStateMsg* msg) {
	Fighter* f = fighters_[msg->clientId_];

	if (f != nullptr) {
		f->setWidth(msg->width_);
		f->setHeight(msg->height_);
		f->setPosition(msg->pos_);
		f->setDirection(msg->dir_);
		f->setVelocity(msg->vel_);
	}
}

void FightersManager::endGame() {
	disableFighters();
}

void FightersManager::killPlayer(Uint8 id) {
	if (fighters_[id] != nullptr)
		fighters_[id]->setActive(false);
}

void FightersManager::enableFighters() {
	for (Fighter* f : fighters_) {
		if (f != nullptr)
			f->setActive(true);
	}
}

void FightersManager::disableFighters() {
	for (Fighter* f : fighters_) {
		if (f != nullptr)
			f->setActive(false);
	}
}
