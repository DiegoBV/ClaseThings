#include "Weapon.h"

Weapon::~Weapon()
{
}

void Weapon::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == disparo) {
			//Calculo de posicion
			Vector2D aux = o->getPosition();
			int x = aux.getX() + o->getWidth() / 2;
			int y = aux.getY() + o->getHeight() / 2;
			Vector2D dirAct = o->getDirection();
			aux.setX(x);
			aux.setY(y);
			dirAct.setX(-dirAct.getX());
			aux = aux + dirAct * (o->getHeight() / 2);

			//calculo de velocidad
			Vector2D vel = dirAct * max(o->getVelocity().magnitude() * 1.5, 2.0);

			//shoot
			stw->shoot(o, aux, vel);
		}
	}
}
