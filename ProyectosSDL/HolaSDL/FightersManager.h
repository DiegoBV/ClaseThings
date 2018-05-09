#pragma once

#include <map>
#include "GameObject.h"
#include "Fighter.h"
#include "FreeMoveInputComponent.h"
#include "CircularMotionPhysics.h"
#include "ImageRenderer.h"
#include "Observer.h"
#include "Observable.h"
#include "SkeletonRenderer.h"
#include "GunInputComponent.h"
#include "NetworkMessenger.h"

/*
 *
 */
class FightersManager : public GameObject, public Observer, public Observable {
public:
	FightersManager(SDLGame* game, NetworkMessenger* nm, BulletsManager* bm);
	virtual ~FightersManager();
	void init();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void receive(Message* msg);
	vector<Fighter*>& getFighters();

private:
	void initFighter(Uint8 id);
	void startGame();
	void endGame();
	void sendPlayerState();
	void updateFighterState(FighterStateMsg* msg);
	void killPlayer(Uint8 id);
	void enableFighters();
	void disableFighters();

	vector<Fighter*> fighters_;

	FreeMoveInputComponent freeMove_;
	CircularMotionPhysics circularMotionPhysics_;
	ImageRenderer fighterImage_;
	SkeletonRendered skeletonRendered_;
	GunInputComponent gun_;

};

