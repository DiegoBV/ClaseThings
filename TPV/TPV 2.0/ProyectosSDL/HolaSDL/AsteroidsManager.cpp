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
	pair<bool, vector<Asteroid*>> aux = renovarPool();
	if (aux.first) { //si ha encontrado alguno inactivo
		Vector2D velIni = aux.second[0]->getVelocity() * 0.52; //CAMBIAR
		Vector2D posIni = aux.second[0]->getPosition();
		int cont = aux.second[0]->getCont();
			for (int i = 0; i < aux.second.size() && i < cont; i++) { //mientras sea menor que el size y el contGeneraciones del asteroide roto
				aux.second[i]->setActive(true);
				aux.second[i]->setVelocity(velIni * (i+1));
				aux.second[i]->setCont(cont - 1);	
				aux.second[i]->setPosition(posIni + Vector2D(rand() % 40, rand() % 40));
			}
			int restantes = cont - aux.second.size(); //asteroides restantes por crear
			for (int i = 0; i < restantes; i++)
				creaItem(velIni * (i + 2) , posIni + Vector2D(rand()%50, rand()% 40), cont - 1);
	}
}

pair<bool, vector<Asteroid*>> AsteroidsManager::renovarPool() { //esto se va a tener q repetir en otras clases... (bulletManager)
	Uint32 i = 0;
	bool encontrado = false;
	vector<Asteroid*> aux;
	while (i < listaAsteroides.size()) {
		if (!listaAsteroides.getItem(i)->isActive()) {
			encontrado = true;
			aux.push_back(listaAsteroides.getItem(i));
		}
		i++;
	}
	pair<bool, vector<Asteroid*>> resultado(encontrado, aux);
	return resultado;
}

void AsteroidsManager::creaItem(Vector2D vel, Vector2D pos, int newCont) {
	Asteroid* newA = new Asteroid(game, vel, pos);
	newA->setCont(newCont);
	listaAsteroides.addNewItem(newA); 
	static_cast<ExampleGame*>(game)->pushObject(newA);
}
