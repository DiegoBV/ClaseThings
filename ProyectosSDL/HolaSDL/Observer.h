#ifndef SRC_OBSERVER_H_
#define SRC_OBSERVER_H_

#include "messages.h"

/*
 *
 */
class Observer {
public:
	Observer();
	virtual ~Observer();
	virtual void receive(Message msg) = 0;
};

#endif /* SRC_OBSERVER_H_ */
