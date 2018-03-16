#ifndef EXAMPLEGAME_H_
#define EXAMPLEGAME_H_

#include <vector>

#include "SDLGame.h"
#include "GameObject.h"
#include "Container.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "ComponentSwitcher.h"
#include "RotationComponent.h"
#include "CircularMotionPhysics.h"
#include "AsteroidsManager.h"
#include "BulletsManager.h"
#include "StarTrekBulletsManager.h"

class ExampleGame: public SDLGame {

public:
	ExampleGame();
	virtual ~ExampleGame();

	// from SDLGame
	void start();
	void stop();
	void pushObject(GameObject* o) { actors_.push_back(o); };

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;
	bool exit_;
	std::vector<GameObject*> actors_;

	Container* leftPaddle_;
	Container* rightPaddle_;
	Container* ball_;
	Fighter* caza_;

	InputComponent* keyboardIC1_;
	InputComponent* keyboardIC2_;
	InputComponent* mouseIC1_;
	InputComponent* accelerationComp;

	PhysicsComponent* paddlePC_;
	PhysicsComponent* paddleAIPC_;
	PhysicsComponent* bouncePC_;
	CircularMotionPhysics* circular_;

	RenderComponent* fillrectRC_;
	RenderComponent* transrectRC_;
	RenderComponent* tennisballRC_;

	RenderComponent* keyIconRC_;
	RenderComponent* mouseIconRC_;
	RenderComponent* aiIconRC_;

	RenderComponent* caza2_;
	InputComponent* rotater;

	ComponentSwitcher* cs1_;
	ComponentSwitcher* cs2_;

	AsteroidsManager* asterManag;
	StarTrekBulletsManager* bullMan;

	bool running_;
	int leftScore_;
	int rightScore_;
};

#endif /* EXAMPLEGAME_H_ */