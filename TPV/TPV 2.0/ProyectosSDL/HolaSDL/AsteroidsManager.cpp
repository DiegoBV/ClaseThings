#include "AsteroidsManager.h"



AsteroidsManager::AsteroidsManager()
{
}


AsteroidsManager::~AsteroidsManager()
{
}

void AsteroidsManager::updatePool() {
	if (!renovarPool()) {
		creaItem();
	}
}

bool AsteroidsManager::renovarPool() { //esto se va a tener q repetir en otras clases... (bulletManager)
	Uint32 i = 0;
	bool encontrado = false;
	while (i < listaAsteroides->size() && !encontrado) {
		if (!listaAsteroides->getItem(i)->isActive()) {
			encontrado = true;
			listaAsteroides->getItem(i)->setActive(true);
		}
		i++;
	}
	return encontrado;
}
