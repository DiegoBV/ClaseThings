#include "GameManager.h"

GameManager::GameManager(SDLGame* game, int winningScore) :
		Container(game), leftScore_(0), rightScore_(0), winningScore_(
				winningScore), running_(false), gameOver_(false) {
}

GameManager::~GameManager() {
}

bool GameManager::isGameOver() const {
	return gameOver_;
}

int GameManager::getLeftScore() const {
	return leftScore_;
}

void GameManager::setLeftScore(int leftScore) {
	leftScore_ = leftScore;
	if (!gameOver_) {
		gameOver_ = (leftScore_ == winningScore_);
	}
}

int GameManager::getRightScore() const {
	return rightScore_;
}

void GameManager::setRightScore(int rightScore) {
	rightScore_ = rightScore;
	if (!gameOver_) {
		gameOver_ = (rightScore_ == winningScore_);
	}
}

bool GameManager::isRunning() const {
	return running_;
}

void GameManager::setRunning(bool running) {
	if (running_ != running) {
		running_ = running;

		Message m = { running ? ROUND_START : ROUND_END };
		send(m);
		if (gameOver_ && running){
			gameOver_ = false;
			setLeftScore(0);
			setRightScore(0);
		}

	}

}

void GameManager::receive(Message msg){
	switch (msg.id_){
		case BALL_LEAVES_RIGHT:
			setRightScore(getRightScore() + 1);
			setRunning(false);
			break;
		case BALL_LEAVES_LEFT:
			setLeftScore(getLeftScore() + 1);
			setRunning(false);
			break;
		default:
			break;
	}
}

