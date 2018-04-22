#pragma once
#include "Weapon.h"
class MultiWeapon :
	public Weapon
{
public:
	MultiWeapon();
	MultiWeapon(SDL_Keycode disparo, Uint8 shotsPerInterval, Uint32  timeInterval, Observer* o, SoundManager* soundManager) : Weapon(disparo, shotsPerInterval, timeInterval,
		o, soundManager) {};
	virtual ~MultiWeapon();
	virtual void shoot(GameObject* o);
};

