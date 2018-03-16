#include "ExampleGame.h"
#include "DemoActor.h"
#include "Collisions.h"
#include "PaddleKeyboardComponent.h"
#include "PaddlePhysicsComponent.h"
#include "FillRectRenderer.h"
#include "PaddleMouseInputComponent.h"
#include "PaddleAIPhysics.h"
#include "TranRectRenderer.h"
#include "BounceOnBordersPhysics.h"
#include "ImageRenderer.h"
#include "AccelerationInputComponent.h"
#include "Weapon.h"
#include "Asteroid.h"
#include "CollisionManager.h"
#include "FightersManager.h"
#include "GameManager.h"

ExampleGame::ExampleGame() :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
	running_ = false;
	leftScore_ = 0;
	rightScore_ = 0;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {
	// hide cursor
	SDL_Rect rect = { 47, 90, 207, 247 };
	SDL_ShowCursor(0);
	Vector2D dirPrub;
	dirPrub.setX(0);
	dirPrub.setY(1);
	Vector2D velPrub;
	velPrub.setX(-1);
	velPrub.setY(-2);
	
	bullMan = new StarTrekBulletsManager(this);

	rotater = new RotationComponent(5, SDLK_RIGHT, SDLK_LEFT);
	accelerationComp = new AccelerationInputComponent(SDLK_UP, SDLK_DOWN, 0.75, 0.5, 20);
	circular_ = new CircularMotionPhysics();

	fillrectRC_ = new FillRectRenderer();
	transrectRC_ = new TranRectRenderer();
	caza2_ = new ImageRenderer(getResources()->getImageTexture(Resources::Airplanes), rect);

	actors_.push_back(bullMan);
	asterManag = new AsteroidsManager(this);
	FightersManager* fMan = new FightersManager(this, bullMan);
	CollisionManager* man = new CollisionManager(this, bullMan, asterManag, fMan);
	GameManager* gm = new GameManager(this);
	asterManag->registerObserver(gm);
	man->registerObserver(gm);
	gm->registerObserver(asterManag);
	gm->registerObserver(fMan);
	actors_.push_back(fMan);
	actors_.push_back(asterManag);
	actors_.push_back(man);
	actors_.push_back(gm);
}

void ExampleGame::closeGame() {
	if (ball_ != nullptr)
		delete ball_;
	if (leftPaddle_ != nullptr)
		delete leftPaddle_;
	if (rightPaddle_ != nullptr)
		delete rightPaddle_;
	if (caza_ != nullptr)
		delete caza_;
}

void ExampleGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		update(startTime);
		render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	// draw score
	/*Texture score(getRenderer(),
			std::to_string(leftScore_) + " - " + std::to_string(rightScore_),
			*(getResources()->getFont(Resources::ARIAL24)),
			{ COLOR(0x111122ff) });
	score.render(getRenderer(), getWindowWidth() / 2 - score.getWidth() / 2,
			10);*/

	// press any key message when game is not running
	/*if (!running_) {
		Texture* hitanykey = getResources()->getTextTexture(
				Resources::PresAnyKey);
		hitanykey->render(getRenderer(),
				getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				getWindowHeight() - hitanykey->getHeight() - 50);
	}*/

	// game over message when game is over
	/*if (leftScore_ == 5 || rightScore_ == 5) {
		Texture* gameOver = getResources()->getTextTexture(Resources::GameOver);
		gameOver->render(getRenderer(),
				getWindowWidth() / 2 - gameOver->getWidth() / 2,
				getWindowHeight() - gameOver->getHeight() - 150);
	}*/

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}
