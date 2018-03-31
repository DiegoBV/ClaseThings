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

	asterManag.registerObserver(&gameManager_);
	colManager.registerObserver(&gameManager_);
	gameManager_.registerObserver(&asterManag);
	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&soundManager_);

	actors_.push_back(&bullMan);
	actors_.push_back(&fightersManager_);
	actors_.push_back(&asterManag);
	actors_.push_back(&colManager);
	actors_.push_back(&gameManager_);
}
void ExampleGame::start() {
	exit_ = false;
	gameManager_.send(&Message(ROUND_START));
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
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			stop();
			break;
		}
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
	this->getResources()->getImageTexture(Resources::Fondo)->render(this->getRenderer(), { 0,0,this->getWindowWidth(), this->getWindowHeight() }, nullptr);
	for (GameObject* o : actors_) {
		o->render(time);
	}
	SDL_RenderPresent(getRenderer());
}

