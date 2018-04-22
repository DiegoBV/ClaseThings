#pragma once
#include "ManagerTemplate.h"
#include "Observable.h"
#include "Bullets.h"

class BulletsManager : public Observable, public Observer
{
public:
	BulletsManager() {}
	virtual ~BulletsManager();
	virtual vector<Bullets*>& getBullets() = 0;
};

