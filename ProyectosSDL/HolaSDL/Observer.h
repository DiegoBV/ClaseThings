#pragma once

#include "GameObject.h"
#include "Messages.h"

/*
 *
 */
class Observer {
public:
	Observer();
	virtual ~Observer();
	virtual void receive(Message* msg) = 0;
};

