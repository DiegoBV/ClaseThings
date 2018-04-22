#include "MultiWeapon.h"



MultiWeapon::MultiWeapon()
{
}


MultiWeapon::~MultiWeapon()
{
}

void MultiWeapon::shoot(GameObject * o)
{
	vector<Vector2D> posiciones;
	vector<Vector2D> velocidades;

	for (int i = 0; i < 6; i++) {
		float cosen = (float)cos(((360 / 6 * (i)))*M_PI / 180);
		float sen = (float)sin((((360 / 6 * (i)))*M_PI / 180));

		Vector2D p;
		int x = o->getPosition().getX() + o->getWidth() / 2;
		int y = o->getPosition().getY() + o->getHeight() / 2;
		p.setX(x);
		p.setY(y);

		int vx = (p.getX()* cosen - p.getY()*sen);
		int vy = (p.getX() * sen + p.getY() * cosen);

		Vector2D dirAct = o->getDirection();
		dirAct.setX(-dirAct.getX());

		Vector2D vel(vx, vy);
		vel.normalize();

		posiciones.push_back(p);
		velocidades.push_back(vel);
	}

	send(&FighterIsShooting(o, posiciones, velocidades));
}
