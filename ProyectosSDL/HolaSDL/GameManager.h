#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Container.h"
#include "Observable.h"
#include "GameCtrlInputComponent.h"
#include "BadgeTimer.h"

/*
 *
 */
class GameManager: public Container, public Observable, public Observer {
public:
	GameManager(SDLGame* game);
	virtual ~GameManager();

	bool isGameOver() const;
	int getLives() const { return lives; };
	bool isRunning() const;
	void setRunning(bool running);
	int getScore() const { return score; };
	void setBadge(bool b) { Badge = b; };
	virtual void receive(Message* msg);
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);

private:
	int lives, score;
	bool Badge;
	int numAstRound = 0;
	//ScoreRenderer scoreRenderer_;
	//LiveRenderer livesRenderer_;
	GameCtrlInputComponent gameCtrl_;
	//GameMsgRenderer gameMsg_;
	BadgeTimer badgeTimer_;
	bool running_;
	bool gameOver_;
};

#endif /* GAMEMANAGER_H_ */
