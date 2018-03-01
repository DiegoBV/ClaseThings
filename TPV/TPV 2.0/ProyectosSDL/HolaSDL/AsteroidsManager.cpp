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
		Vector2D velIni = aux.second[0]->getVelocity() * 2; //CAMBIAR
		Vector2D posIni = aux.second[0]->getPosition();
			for (int i = 0; i < aux.second.size() && i < aux.second[0]->getCont(); i++) { //mientras sea menor que el size y el contGeneraciones del asteroide roto
				aux.second[i]->setActive(true);
				//Vector2D vel = aux.second[0]->getVelocity() *(i + 1) * 0.1;
				aux.second[i]->setVelocity(velIni);
				Vector2D posaux(rand() % 20, rand()%30);
				aux.second[i]->setPosition(posIni + posaux);
			}
			int restantes = aux.second[0]->getCont() - aux.second.size(); //asteroides restantes por crear
			if (restantes > 0) {
				for (int i = 0; i < restantes; i++)
					creaItem(velIni, posIni);
			}
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

void AsteroidsManager::creaItem(Vector2D vel, Vector2D pos) {
	Asteroid* newA = new Asteroid(game, vel, pos);  
	listaAsteroides.addNewItem(newA); 
	static_cast<ExampleGame*>(game)->pushObject(newA);
}
