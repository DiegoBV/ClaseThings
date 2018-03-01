#include "Asteroid.h"



Asteroid::Asteroid()
{
}


Asteroid::~Asteroid()
{
}

void Asteroid::split() {
	if (contGeneraciones > 1) {
		setActive(false);
	}
}
