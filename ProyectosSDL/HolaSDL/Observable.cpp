#include "Observable.h"

Observable::Observable() : observers_() {

}

Observable::~Observable() {
	// TODO Auto-generated destructor stub
}

void Observable::send(Message* msg) {
	for( Observer* o : observers_ ) {
		o->receive(msg);
	}


}

void Observable::registerObserver(Observer* o) {
	observers_.push_back(o);
}
