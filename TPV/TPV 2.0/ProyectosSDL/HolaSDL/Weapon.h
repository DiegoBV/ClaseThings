#pragma once
#include "InputComponent.h"
#include "BulletsManager.h"
class Weapon : public InputComponent
{
private:
	BulletsManager* stw;
	SDL_Keycode disparo;
public:
	Weapon(BulletsManager* stw, SDL_Keycode disparo) : stw(stw), disparo(disparo) {};
	virtual ~Weapon();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
	double max(double i, double p) { if (i > p) { return i; } else { return p; } };
};

