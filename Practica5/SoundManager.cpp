#include "SoundManager.h"
#include "messages.h"
#include "SDLGame.h"

SoundManager::SoundManager(SDLGame* game) : Container(game) {
	// TODO Auto-generated constructor stub

}

SoundManager::~SoundManager() {
	// TODO Auto-generated destructor stub
}

void SoundManager::update(Uint32 time){

	while (!eventQueue.empty()) {
		game_->getResources()->getSoundEffect(eventQueue.front().id_)->play(eventQueue.front().num_);
		eventQueue.pop();
	}
}

void SoundManager::receive(Message* msg) {
	switch (static_cast<Message*>(msg)->id_) {
	case FIGHTER_SHOOT:
		eventQueue.push(PlayMessage(Resources::GunShot, 0));
		break;

	case BULLET_ASTROID_COLLISION:
		eventQueue.push(PlayMessage(Resources::ExplosionSound, 0));
		break;

	case ASTROID_FIGHTER_COLLISION:
		eventQueue.push(PlayMessage(Resources::ExplosionSound, 0));
		break;

	case ROUND_START:
		game_->getResources()->getMusic(Resources::ImperialMarch)->play(3);
		break;

	case ROUND_OVER:
		game_->getResources()->getMusic(Resources::ImperialMarch)->stop();
		break;
	}
}
