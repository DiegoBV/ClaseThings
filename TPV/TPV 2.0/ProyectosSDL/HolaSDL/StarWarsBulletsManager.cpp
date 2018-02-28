#include "StarWarsBulletsManager.h"
#include "Container.h"
#include "FillRectRenderer.h"
#include "BasicMotionPhysics.h"

StarWarsBulletsManager::~StarWarsBulletsManager()
{
}

void StarWarsBulletsManager::shoot(GameObject* o, Vector2D p, Vector2D v) {
	//Creamos el nuevo game component
	Container* newCmp = new Container(this->getGame());

	//Creamos los metodos basicos de render y fisicas
	FillRectRenderer* fillRect = new FillRectRenderer();
	BasicMotionPhysics* motion = new BasicMotionPhysics();

	//añadimos dichos metodos al Container
	newCmp->addPhysicsComponent(motion);
	newCmp->addRenderComponent(fillRect);

	//establecemos su tamaño y lo añadimos a la lista de balas
	newCmp->setHeight(5);
	newCmp->setWidth(5);
	newCmp->setVelocity(v);
	newCmp->setPosition(p);
	bullets.push_back(newCmp);
}

void StarWarsBulletsManager::update(Uint32 time) {
	vector<GameObject*>::iterator go;
	for (go = bullets.begin(); go != bullets.end();) {
		static_cast<GameObject*>(*go)->update(time);
		Vector2D aux = static_cast<GameObject*>(*go)->getPosition();
		if (aux.getX() > this->getGame()->getWindowWidth() || aux.getY() > this->getGame()->getWindowHeight() || aux.getX() < 0 || aux.getY() < 0) {
			delete *go;
			go = bullets.erase(go);
		}
		else {
			++go;
		}
	}
}

void StarWarsBulletsManager::render(Uint32 time) {
	for (GameObject* go : bullets) {
		go->render(time);
	}
}
