#include "BadgeTimer.h"
#include "GameManager.h"


BadgeTimer::BadgeTimer()
{
}


BadgeTimer::~BadgeTimer()
{
}

void BadgeTimer::update(GameObject* o, Uint32 time) {
	if (on_ && (timeOn_ + timeInterval_) < time) { //se acaba el tiempo del superArma
		GameManager* gm = dynamic_cast<GameManager*>(o);
            if (gm != nullptr) { //asegurarnos de que es un gameManager
			gm->setBadge(false);
			on_ = false;
			timeOn_ = 0;
		}
	}
}

void BadgeTimer::start(Uint32 timeInterval) {
	on_ = true; //timer activo
	timeOn_ = SDL_GetTicks(); //ticks de sdl
	timeInterval_ = timeInterval;
}
