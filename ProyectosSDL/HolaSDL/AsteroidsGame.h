#pragma once

#include <vector>

#include "AsteroidsManager.h"
#include "SDLGame.h"
#include "GameObject.h"
#include "FightersManager.h"
#include "GameManager.h"
#include "CollisionManager.h"
#include "NetworkMessenger.h"

class AsteroidsGame: public SDLGame {

public:
	AsteroidsGame(char* host, int port);
	virtual ~AsteroidsGame();

	// from SDLGame
	void start();
	void stop();

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
	char* host_;
	int port_;

	NetworkMessenger networkMessenger_;
	GameManager gameManager_;
	BulletsManager bulletsManager_;
	FightersManager fightersManager_;
	AsteroidsManager asteroidsManager_;
	CollisionManager collisionManager_;
};

