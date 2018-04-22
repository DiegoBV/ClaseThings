#ifndef SRC_OBSERVABLE_H_
#define SRC_OBSERVABLE_H_

#include "Observer.h"
#include <vector>
#include "messages.h"

/*
 *
 */
class Observable {
public:
	Observable();
	virtual ~Observable();
	virtual void send(Message* msg);
	virtual void registerObserver(Observer* o);
private:
	std::vector<Observer*> observers_;
};

#endif /* SRC_OBSERVABLE_H_ */
