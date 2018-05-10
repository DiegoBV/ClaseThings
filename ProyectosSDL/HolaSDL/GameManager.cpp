#include "GameManager.h"


GameManager::GameManager(SDLGame* game) :
		Container(game), gameMsgRenderer_(), gameCtrlInputComponent_(), connectedPlayersRenderer_(), playerInfoRenderer_(), state_(
				WAITING), players_(), numOfConnectedPlayers_(0), alivePlayers_(
				0) {

	timer_.registerObserver(this);

	addRenderComponent(&gameMsgRenderer_);
	//addRenderComponent(&connectedPlayersRenderer_);
	addRenderComponent(&playerInfoRenderer_);
	addInputComponent(&gameCtrlInputComponent_);
	addPhysicsComponent(&timer_);
}

GameManager::~GameManager() {
}

GameManager::GameState GameManager::getState() {
	return state_;
}

void GameManager::init() {
	registerPlayer(getGame()->getClientId());

	JoiningGameMsg msg = { getGame()->getClientId() };
	send(&msg);
	sendClientInfo();
}

// this method is called only from the InputComponent that starts the game
void GameManager::start() {
	if (state_ == READY || state_ == OVER) {
		startGame();
		Message msg = { GAME_START };
		send(&msg);
	}
}

void GameManager::receive(Message* msg) {
	switch (msg->mType_) {
	case JOINING_GAME:
		sendClientInfo();
		break;
	case PLAYER_INFO:
		registerPlayer(static_cast<PlayerInfoMsg*>(msg)->clientId_);
		break;
	case GAME_IS_READY:
		getReady();
		break;
	case GAME_START:
		timer_.setOn(true);
		startGame();
		break;
	case GAME_OVER:
		endGame();
		break;
	case BULLET_FIGHTER_COLLISION:
		killPlayer(static_cast<BulletFighterCollisionMsg*>(msg)->fighterId_);
		break;
	case TIME_HAS_PASSED:
		if (getGame()->isMasterClient()) { //si es el master, anyade asteroides
			send(&Message(ADD_ASTEROID)); 
			cout << "sending" << endl;
		}
		break;
	case ASTEROID_ADDED:
		if (getGame()->isMasterClient()) {
			msg->mType_ = NEW_ASTEROID_INCOMING;
			send(msg);
			cout << "mandando info a otros players";
		}
		break;
	case NEW_ASTEROID_INCOMING:
		msg->mType_ = ADDING_ASTEROID;
		send(msg);
		break;
	}
}

int GameManager::getNumOfConnectedPlayers() {
	return numOfConnectedPlayers_;
}

void GameManager::registerPlayer(Uint8 id) {
	if (id >= players_.size()) {
		players_.resize(id + 1);
	}
	if (!players_[id].connected_) {
		players_[id].id_ = id;
		players_[id].connected_ = true;
		players_[id].alive_ = true;
		numOfConnectedPlayers_++;

		if (getGame()->isMasterClient()) {
			if (numOfConnectedPlayers_ == NUM_OF_PLAYERS) {
				Message msg = { GAME_IS_READY };
				send(&msg);
				getReady();
			}
		}

	}
}

void GameManager::sendClientInfo() {
	PlayerInfoMsg msg = { getGame()->getClientId() };
	send(&msg);
}

void GameManager::getReady() {
	if (state_ == WAITING) {
		state_ = READY;
	}
}

void GameManager::endGame() {
	if (state_ == RUNNING) {
		state_ = OVER;
	}
}

void GameManager::startGame() {
	if (state_ != WAITING) {
		alivePlayers_ = numOfConnectedPlayers_;
		for (PlayerInfo& p : players_) { // the use of & is important
			p.alive_ = true;
		}
		state_ = RUNNING;
	}
}

vector<GameManager::PlayerInfo>& GameManager::getPlayereInfo() {
	return players_;
}

// the game is over when 1 or 0 players remain (0 because they can be killed at the same time)
void GameManager::checkIfGameIsOver() {
	if (alivePlayers_ < 2) {
		Message msg = { GAME_OVER };
		send(&msg);
		endGame();
	}
}

void GameManager::killPlayer(Uint8 id) {
	if (players_[id].alive_) {
		players_[id].alive_ = false;
		alivePlayers_--;
		if (getGame()->isMasterClient()) {
			checkIfGameIsOver();
		}
	}
}
