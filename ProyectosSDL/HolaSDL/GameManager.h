#pragma once

#include "Container.h"
#include "Observer.h"
#include "Observable.h"
#include "GameCtrlInputComponent.h"
#include "ConnectedPlayersRenderer.h"
#include "GameStatusRenderer.h"
#include "PlayersInfoRenderer.h"
#include "Timer.h"

/*
 *
 */
class GameManager: public Container, public Observer, public Observable {
public:
	enum GameState {
		WAITING, READY, RUNNING, OVER
	};

	struct PlayerInfo {
		PlayerInfo() {
			id_ = -1;
			connected_ = false;
			alive_ = false;
		}
		Uint8 id_;
		bool connected_;
		bool alive_;
	};

	GameManager(SDLGame* game);
	virtual ~GameManager();
	GameState getState();
	void init();
	void start();
	int getNumOfConnectedPlayers();
	virtual void receive(Message* msg);
	vector<PlayerInfo>& getPlayereInfo();

private:
	void registerPlayer(Uint8 id);
	void sendClientInfo();
	void getReady();
	void startGame();
	void endGame();
	void killPlayer(Uint8 id);
	void checkIfGameIsOver();

	static int const NUM_OF_PLAYERS = 2;

	GameStatusRenderer gameMsgRenderer_;
	GameCtrlInputComponent gameCtrlInputComponent_;
	ConnectedPlayersRenderer connectedPlayersRenderer_;
	PlayersInfoRenderer playerInfoRenderer_;

	GameState state_;

	Timer timer_;

	vector<PlayerInfo> players_;
	int numOfConnectedPlayers_;
	int alivePlayers_;
};

