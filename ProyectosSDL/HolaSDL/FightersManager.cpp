#include "FightersManager.h"

FightersManager::FightersManager(SDLGame * game, BulletsManager * bulletsManager) : GameObject(game)
{
	fighter_ = Fighter(game);
	weaponComp_ = Weapon(bulletsManager, SDLK_SPACE, 1, 15, &fighter_);
	weaponComp2_ = Weapon(bulletsManager, SDLK_SPACE, 1, 15, &fighter_);
	circularMotionComp_ = CircularMotionPhysics();
	accelerationComp_ = AccelerationInputComponent();
	imageRenderComp_ = ImageRenderer();
	rotationComp_ = RotationComponent();
}

FightersManager::~FightersManager()
{
}

void FightersManager::handleInput(Uint32 time, const SDL_Event & event)
{
}

void FightersManager::update(Uint32 time)
{
	fighter_.update(time);
}

void FightersManager::render(Uint32 time)
{
	fighter_.render(time);
}

Fighter * FightersManager::getFighter()
{
	return &fighter_;
}

void FightersManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ROUND_START:
		break;
//	case ROUND_END:
	//	break;
	case BADGE_ON:
		break;
	case BADGE_OFF:
		break;
	}
}
