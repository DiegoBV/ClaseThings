#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "Fighter.h"
#include "CircularMotionPhysics.h"
#include "AccelerationInputComponent.h"
#include "ImageRenderer.h"
#include "RotationComponent.h"
#include "Weapon.h"

class FightersManager :
	public GameObject, public Observer
{
public:
	FightersManager(SDLGame* game, Observer* bulletsManager);
	~FightersManager();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	Fighter* getFighter();
	virtual void receive(Message* msg);

protected:

	Fighter fighter_;
	CircularMotionPhysics circularMotionComp_;
	AccelerationInputComponent accelerationComp_;
	ImageRenderer imageRenderComp_;
	RotationComponent rotationComp_;
	Weapon weaponComp_;  //Esta es el arma normal del fighter
	Weapon weaponComp2_; //Arma secundaria
	//Falta el componente de render para indicar que tiene el arma secundaria, sin prisas. 

};

