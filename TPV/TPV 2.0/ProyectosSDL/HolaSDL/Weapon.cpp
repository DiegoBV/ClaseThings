#include "Weapon.h"

Weapon::~Weapon()
{
}

void Weapon::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {
	auxTime++; //aumento de la variable que controla el intervalo de tiempo
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == disparo) {
			if(puedeDisparar())
				shoot(o);
		}
	}
}

bool Weapon::puedeDisparar() {
	if (auxTime > timeInterval) { //ha pasado un inteervalo de tiempo
		auxShots = 0;
		auxTime = 0; //reinicio variables, devuelvo false
		return false;
	}
	else if (auxShots >= shotsPerInterval) { //si el intervalo no ha pasado y se pasa de disparos, devuelve false
		return false;
	}
	else { //si no ha pasado el intervalo de tiempo y puede seguir disparando, sumo variables y devuelvo true
		auxShots++;
		return true;
	}
		
}

void Weapon::shoot(GameObject* o) {
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
	stw->shoot(aux, vel);
}