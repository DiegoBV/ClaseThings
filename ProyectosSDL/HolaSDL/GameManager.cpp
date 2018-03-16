#include "GameManager.h"

GameManager::GameManager(SDLGame* game) :
		Container(game), running_(true), gameOver_(false), lives(3) {
	badgeTimer_.start(100);
}

GameManager::~GameManager() {
}

bool GameManager::isGameOver() const {
	return gameOver_;
}

bool GameManager::isRunning() const {
	return running_;
}

void GameManager::setRunning(bool running) { //esto indica ronda
	if (running_ != running) {
		running_ = running;
		Message m = { running ? ROUND_START : ROUND_OVER };
		send(&m);
		if (gameOver_ && running){
			gameOver_ = false;
		}
	}
}

void GameManager::handleInput(Uint32 time, const SDL_Event& event) {
	gameCtrl_.handleInput(this, time, event);
	Container::handleInput(time, event);
}

void GameManager::receive(Message* msg){
	switch (msg->id_){
		case ASTROID_FIGHTER_COLLISION:
			this->lives--; //si no quedan mas vidas, acabaria el juego, si no, acaba una ronda
			if (getLives() == 0) { gameOver_ = true;}
			else { setRunning(false); }
			setBadge(false);
			numAstRound = 0;
			break;
		case BULLET_ASTROID_COLLISION:
			this->score++; 
			if (numAstRound == 10) { 
				numAstRound = 0;
				setBadge(true); 
			}
			else {
				numAstRound++;
			}
			break;
		case NO_MORE_ATROIDS:
			//acabar ronda, acaba juego
			setBadge(false);
			gameOver_ = true;
			//ronda (?)
			break;
		case BADGE_ON:
			badgeTimer_.start(100);
			break;
	}
}

void GameManager::update(Uint32 time) {
	badgeTimer_.update(this, time);
	Container::update(time);
}

