#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Container.h"
#include "Observable.h"
#include "GameCtrlInputComponent.h"
#include "GameMsgRenderer.h"
#include "BadgeTimer.h"
#include "ScoreRenderer.h"
#include "LiveRenderer.h"
#include "BadgeObject.h"

/*
 *
 */
class GameManager: public Container, public Observable, public Observer {
public:
	GameManager() {};
	GameManager(SDLGame* game);
	virtual ~GameManager();

	bool isGameOver() const;
	int getLives() const { return lives; };
	bool isRunning() const;
	void setRunning(bool running);
	void setGameOver(bool gameO) { gameOver_ = gameO; };
	int getScore() const { return score; };
	void setBadge(bool b) { Badge = b; };
	virtual void receive(Message* msg);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
	void setLives(int nLives) { this->lives = nLives; }

private:
	int lives, score;
	bool Badge;
	int numAstRound = 0;
	ScoreRenderer scoreRenderer_;
	LiveRenderer livesRenderer_;
	GameCtrlInputComponent gameCtrl_;
	GameMsgRenderer gameMsg_;
	BadgeTimer badgeTimer_;
	BadgeObject badgeObject_;
	bool running_;
	bool gameOver_;
};

#endif /* GAMEMANAGER_H_ */
