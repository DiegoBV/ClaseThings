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
#include "FightersManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "GameManager.h"

class ExampleGame: public SDLGame {

public:
	ExampleGame();
	virtual ~ExampleGame();

	// from SDLGame
	void start();
	void stop();

private:
	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;
	bool exit_;
	std::vector<GameObject*> actors_;

	Texture fondo;
	SoundManager soundManager_{ this };
	StarTrekBulletsManager bullMan{ this };
	AsteroidsManager asterManag{ this };
	FightersManager fightersManager_{ this, &bullMan, &soundManager_};
	CollisionManager colManager{ this, &bullMan, &asterManag, &fightersManager_, &soundManager_ };
	GameManager gameManager_{ this };

	void initGame();
	void closeGame() {};
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	bool running_;
	int leftScore_;
	int rightScore_;
};

#endif /* EXAMPLEGAME_H_ */
