#include "DeActivateOnBorderExit.h"

DeActivateOnBorderExit::DeActivateOnBorderExit() {
	// TODO Auto-generated constructor stub

}

DeActivateOnBorderExit::~DeActivateOnBorderExit() {
	// TODO Auto-generated destructor stub
}

void DeActivateOnBorderExit::update(GameObject* o, Uint32 time) {
	if (o->getPosition().getX() < 0
			|| o->getPosition().getX() > o->getGame()->getWindowWidth()
			|| o->getPosition().getY() < 0
			|| o->getPosition().getY() > o->getGame()->getWindowHeight()) {
		o->setActive(false);
	}

}
