#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "Fighter.h"
#include "ComponentSwitcher.h"
#include "CircularMotionPhysics.h"
#include "AccelerationInputComponent.h"
#include "ImageRenderer.h"
#include "RotationComponent.h"
#include "Weapon.h"
#include "SoundManager.h"
#include "MultiWeapon.h"

class FightersManager :
	public GameObject, public Observer, public Observable
{
protected:
	Fighter fighter_;
	CircularMotionPhysics circularMotionComp_;
	AccelerationInputComponent accelerationComp_;
	ImageRenderer imageRenderComp_;
	RotationComponent rotationComp_;
	Weapon weaponComp_;  //Esta es el arma normal del fighter
	Weapon weaponComp2_; //Arma secundaria
	MultiWeapon multiWeapon_;
	bool superWeapon_ = false;
	enum weaponType {
		Badge, SupahBullets, MultahBullets
	};
	weaponType weapon_ = Badge;
public:
	FightersManager() {};
	FightersManager(SDLGame* game, Observer* bulletsManager, SoundManager* soundManager);
	virtual ~FightersManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	void switcherSup();
	void switcherNor();

	Fighter* getFighter();
	virtual void receive(Message* msg);
};

