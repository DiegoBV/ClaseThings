#include "FightersManager.h"

FightersManager::FightersManager(SDLGame * game, Observer* bulletsManager) : GameObject(game)
{
	SDL_Rect rect = { 47, 90, 207, 247 };
	fighter_ = Fighter(game);
	weaponComp_ = Weapon(SDLK_SPACE, 1, 50, bulletsManager);
	weaponComp2_ = Weapon(SDLK_SPACE, 1, 10, bulletsManager);
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

void FightersManager::switcherSup()
{
	if (!superWeapon_) {
      	fighter_.delInputComponent(&weaponComp_);
		fighter_.addInputComponent(&weaponComp2_);
		superWeapon_ = true;
	}
}

void FightersManager::switcherNor()
{
	if (superWeapon_) {
		fighter_.delInputComponent(&weaponComp2_);
		fighter_.addInputComponent(&weaponComp_);
		superWeapon_ = false;
	}
}
Fighter * FightersManager::getFighter()
{
	return &fighter_;
}

void FightersManager::receive(Message * msg)
{
	switch (msg->id_) {
	case ROUND_START:
		fighter_.setPosition(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
		fighter_.setActive(true);
		fighter_.setVelocity(Vector2D(0.0, 0.0));
		fighter_.setDirection(Vector2D(0.0, -1.0));
		break;
	case ROUND_OVER:
		fighter_.setActive(false);
		break;
	case BADGE_ON:
		switcherSup();
		break;
	case BADGE_OFF:
		switcherNor();
		break;
	}
}
