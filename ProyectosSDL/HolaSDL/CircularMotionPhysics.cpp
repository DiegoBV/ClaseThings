#include "CircularMotionPhysics.h"


CircularMotionPhysics::CircularMotionPhysics()
{
}


CircularMotionPhysics::~CircularMotionPhysics()
{
}

void CircularMotionPhysics::update(GameObject* o, Uint32 time){
	Vector2D temp = o->getPosition() + o->getVelocity();

	if (temp.getX() >= o->getGame()->getWindowWidth()){
		temp.setX(0);
	}
	else if (temp.getX() <= 0){
		temp.setX(o->getGame()->getWindowWidth());
	}
	else if (temp.getY() >= o->getGame()->getWindowHeight()){
		temp.setY(0);
	}
	else if (temp.getY() <= 0){
		temp.setY(o->getGame()->getWindowHeight());
	}

	o->setPosition(temp);
}
