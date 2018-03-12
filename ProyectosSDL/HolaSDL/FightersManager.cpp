#include "FightersManager.h"

FightersManager::FightersManager(SDLGame * game, Observer* bulletsManager) : GameObject(game)
{
	SDL_Rect rect = { 47, 90, 207, 247 };
	fighter_ = Fighter(game);
	weaponComp_ = Weapon(SDLK_SPACE, 1, 5, bulletsManager);
	weaponComp2_ = Weapon(SDLK_SPACE, 1, 15, bulletsManager);
	circularMotionComp_ = CircularMotionPhysics();
	accelerationComp_ = AccelerationInputComponent(SDLK_UP, SDLK_DOWN, 0.75, 0.5, 20);
	imageRenderComp_ = ImageRenderer(game->getResources()->getImageTexture(Resources::Airplanes), rect);
	rotationComp_ = RotationComponent(5, SDLK_RIGHT, SDLK_LEFT);
	fighter_.addInputComponent(&weaponComp_);
	fighter_.addPhysicsComponent(&circularMotionComp_);
	fighter_.addInputComponent(&accelerationComp_);
	fighter_.addInputComponent(&rotationComp_);
	fighter_.addRenderComponent(&imageRenderComp_);
	fighter_.setWidth(30);
	fighter_.setHeight(30);
	fighter_.setPosition(Vector2D(game->getWindowWidth()/ 2 - 6, game->getWindowHeight() / 2 - 6));
	fighter_.setVelocity(Vector2D(-1, -2));
}

FightersManager::~FightersManager()
{
}

void FightersManager::handleInput(Uint32 time, const SDL_Event & event)
{
	fighter_.handleInput(time, event);
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
	case ASTROID_FIGHTER_COLLISION:
		fighter_.setActive(false);
		break;
	}

}
