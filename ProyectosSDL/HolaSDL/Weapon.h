#pragma once
#include "InputComponent.h"
#include "BulletsManager.h"
#include "Observable.h"
#include "Observer.h"
#include "Fighter.h"
#include "SoundManager.h"

class Weapon : public InputComponent, public Observable
{
private:
	SDL_Keycode disparo;
	Uint8 shotsPerInterval;
	Uint32  timeInterval;
	Uint8 auxShots;
	Uint32 auxTime;
	SoundManager* soundManager_;
	void updateVariables();

public:
	Weapon() {}
	Weapon(SDL_Keycode disparo, Uint8 shotsPerInterval, Uint32  timeInterval, Observer* o, SoundManager* soundManager) : disparo(disparo), 
				shotsPerInterval(shotsPerInterval), timeInterval(timeInterval), auxShots(0), auxTime(0), soundManager_(soundManager) {
		registerObserver(o);
		registerObserver(soundManager_);
	};

	virtual ~Weapon();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	double max(double i, double p) { if (i > p) { return i; } else { return p; } };
	bool puedeDisparar();
	void shoot(GameObject* o);
};

