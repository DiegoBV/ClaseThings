#include "Observable.h"

Observable::Observable() {
}

Observable::~Observable() {
}

void Observable::registerObserver(Observer* o) {
	observers_.push_back(o);
}

void Observable::removeObserver(Observer* o) {
	std::vector<Observer*>::iterator position = std::find(observers_.begin(),
			observers_.end(), o);
	if (position != observers_.end())
		observers_.erase(position);
}

void Observable::send(Message* msg) {
	for( Observer* o : observers_ ) {
		o->receive(msg);
	}
}
