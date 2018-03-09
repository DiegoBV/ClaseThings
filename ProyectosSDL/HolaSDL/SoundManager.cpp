#include "SoundManager.h"
#include "messages.h"

SoundManager::SoundManager(SDLGame* game) : game_(game) {
	// TODO Auto-generated constructor stub

}

SoundManager::~SoundManager() {
	// TODO Auto-generated destructor stub
}

void SoundManager::receive(Message msg) {
	switch ( msg.id_ ) {
	/*case BALL_TOUCHES_WALL:
		game_->getResources()->getSoundEffect(Resources::Wall_Hit)->play(0);
		break;
	case BALL_TOUCHES_PADDLE:
		game_->getResources()->getSoundEffect(Resources::Paddle_Hit)->play(0);
		break;
	case ROUND_START:
		game_->getResources()->getMusic(Resources::Beat)->play(-1);
		break;
	case ROUND_END:
		game_->getResources()->getMusic(Resources::Beat)->stop();
		break;
		*/

	}
}
