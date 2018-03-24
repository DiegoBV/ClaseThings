#pragma once
#include "PhysicsComponent.h"
class BadgeTimer :
	public PhysicsComponent
{
public:
	BadgeTimer();
	virtual ~BadgeTimer();
	virtual void update(GameObject* o, Uint32 time);
	void start(Uint32 timeInterval);

private:
	bool on_;
	Uint32 timeOn_ = 0;
	Uint32 timeInterval_;
};

