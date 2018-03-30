#include "GameManager.h"

GameManager::GameManager(SDLGame* game) :
		Container(game), running_(true), gameOver_(false), lives(3) {
	this->addRenderComponent(&scoreRenderer_);
	this->addRenderComponent(&gameMsg_);
	this->addRenderComponent(&livesRenderer_);
	this->addInputComponent(&gameCtrl_);
	badgeObject_ = (game);
	this->registerObserver(&badgeObject_);
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
			score = 0; //score a 0 si pierdes
		}
	}
}

void GameManager::receive(Message* msg){
	switch (msg->id_){
		case ASTROID_FIGHTER_COLLISION:
			this->lives--; //si no quedan mas vidas, acabaria el juego, si no, acaba una ronda
			if (getLives() <= 0) { gameOver_ = true; setRunning(false); }
			else { setRunning(false); }
			setBadge(false);
			numAstRound = 0;
			break;
		case BULLET_ASTROID_COLLISION:
			this->score++; 
			if (numAstRound >= 1) { 
				numAstRound = 0;
				setBadge(true);
				badgeTimer_.start(10000);  
			}
			else if(!this->Badge){
				numAstRound++;
			}
			break;
		case NO_MORE_ATROIDS:
			//acabar ronda, acaba juego
			setBadge(false);
			gameOver_ = true;
			setRunning(false);
			break;
		case BADGE_ON:
			badgeTimer_.start(100);
			break;
	}
}

void GameManager::render(Uint32 time){
	badgeObject_.render(time);
	Container::render(time);
}

void GameManager::update(Uint32 time) {
	badgeTimer_.update(this, time);
	if (Badge) {
		send(&Message(BADGE_ON));
	}
	else {
		send(&Message(BADGE_OFF));
	}
	Container::update(time);
}

