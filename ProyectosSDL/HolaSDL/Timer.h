#pragma once
#include "PhysicsComponent.h"
#include "Observable.h"
class Timer :
	public PhysicsComponent, public Observable
{
private:
	const Uint32 SECS = 5000;
	bool on_ = false;
	Uint32 timeOn_ = 0;

public:
	Timer();
	virtual ~Timer();
	virtual void update(GameObject* o, Uint32 time);
	void setOn(bool b) { on_ = b; timeOn_ = SDL_GetTicks(); };
};

