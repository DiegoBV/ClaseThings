#include "AsteroidsManager.h"
#include "ExampleGame.h"
#include <algorithm>
AsteroidsManager::AsteroidsManager()
{
}


AsteroidsManager::~AsteroidsManager()
{
}

AsteroidsManager::AsteroidsManager(SDLGame* game, vector<Asteroid*> asteroides): game(game) {
	for (int i = 0; i < asteroides.size(); i++) {
		listaAsteroides.addNewItem(asteroides[i]); //nno se añaden bien
		registerObserver(asteroides[i]);
		static_cast<ExampleGame*>(game)->pushObject(asteroides[i]);
		//listaAsteroides.get().push_back[&asteroides[i]];
	}
}
void AsteroidsManager::updatePool() {

	pair<bool, Asteroid**> par = listaAsteroides.getObjectPool(); //siempre se encontrará uno inactivo (el disparado)
	Vector2D velIni = (*par.second)->getVelocity();
	Vector2D posIni = (*par.second)->getPosition();
	int cont = (*par.second)->getCont();
	int i = 0;
	while (i < cont) {
		par = listaAsteroides.getObjectPool(); //si encuentra objetos inactivos, los activa, si no, crea nuevos
		(*par.second)->setVelocity(velIni * 0.53 * (i + 1));
		(*par.second)->setPosition(posIni + Vector2D(rand() % 40, rand() % 40));
		if (!par.first) { //si se cumple, significa que ha creado uno nuevo, por lo tanto se debe pushear a la lista del game para que se pinte, se actualice...
			Asteroid* puntero = new Asteroid(**par.second); //4 now
			static_cast<ExampleGame*>(game)->pushObject(puntero);
		}
		i++;
	}
}