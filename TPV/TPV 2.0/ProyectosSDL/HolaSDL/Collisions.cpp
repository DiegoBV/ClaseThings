#include "Collisions.h"

Collisions::Collisions() {
	// TODO Auto-generated constructor stub

}

Collisions::~Collisions() {
	// TODO Auto-generated destructor stub
}

bool Collisions::collides(GameObject* o1, GameObject* o2) {

	Vector2D o1Pos = o1->getPosition();
	double o1Width = o1->getWidth();
	double o1Height = o1->getHeight();

	Vector2D o2Pos = o2->getPosition();
	double o2Width = o2->getWidth();
	double o2Height = o2->getHeight();

	// o1 completely to the left of o2, or vice versa
	if (o1Pos.getX() + o1Width < o2Pos.getX()
			|| o2Pos.getX() + o2Width < o1Pos.getX()) {
		return false;
	}

	// o1 completely to the top of o2, or vice versa
	if (o1Pos.getY() + o1Height < o2Pos.getY()
			|| o2Pos.getY() + o2Height < o1Pos.getY()) {
		return false;
	}

	return true;
}
