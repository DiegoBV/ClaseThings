#include "SoundManager.h"
#include "messages.h"
#include "SDLGame.h"

SoundManager::SoundManager(SDLGame* game) : game_(game) {
	// TODO Auto-generated constructor stub

}

SoundManager::~SoundManager() {
	// TODO Auto-generated destructor stub
}

void SoundManager::receive(Message* msg) {
	switch (static_cast<Message*>(msg)->id_) {
	case FIGHTER_SHOOT:
		game_->getResources()->getSoundEffect(Resources::GunShot)->play(0);
		break;

	case BULLET_ASTROID_COLLISION:
		game_->getResources()->getSoundEffect(Resources::ExplosionSound)->play(0);
		break;

	case ASTROID_FIGHTER_COLLISION:
		game_->getResources()->getSoundEffect(Resources::ExplosionSound)->play(0);
		break;

	case ROUND_START:
		game_->getResources()->getMusic(Resources::ImperialMarch)->play(3);
		break;

	case ROUND_OVER:
		game_->getResources()->getMusic(Resources::ImperialMarch)->stop();
		break;
	}
}
