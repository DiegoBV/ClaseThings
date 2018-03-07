#pragma once
#include "GameObject.h"
#include "ManagerTemplate.h"
#include "Observable.h"
#include "Container.h"
#include "Bullets.h"

class BulletsManager : public Observable, public Observer
{
public:
	BulletsManager() {}
	virtual ~BulletsManager();
	virtual vector<Bullets*>& getBullets() = 0;
};

