#pragma once

#include "Observer.h"
#include <vector>

/*
 *
 */
class Observable {
public:
	Observable();
	virtual ~Observable();
	virtual void registerObserver(Observer* o);
	virtual void removeObserver(Observer* o);
	virtual void send(Message* msg);
private:
	std::vector<Observer*> observers_;
};

