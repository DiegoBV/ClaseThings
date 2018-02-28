#pragma once
#include "ManagerTemplate.h"
#include "GameObject.h"
class AsteroidsManager
{
private:
	ManagerTemplate<GameObject*>* listaAsteroides; //cambiar GO x gameObject, no sé si se hereda o se incluye la template
public:
	AsteroidsManager();
	~AsteroidsManager();
	void updatePool();
	bool renovarPool();
	//void creaItem() {listaAsteroides->addItem(new Asteroid())};
};

