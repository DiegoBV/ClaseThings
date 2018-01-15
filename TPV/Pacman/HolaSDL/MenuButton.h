#pragma once
#include "GameObject.h"
#include "Texture.h"
class MenuButton: public GameObject
{
	int x, y, w, h;
	Texture* boton;
public:
	MenuButton(int x, int y, int w, int h, Texture * txt, Game* game) : x(x), y(y), w(w), h(h), boton(txt), GameObject(game) {}
	~MenuButton();
	virtual void render();
	//virtual void update();
	/*virtual bool handleEvent(SDL_Event& e) {
		if (...ratonPulsado) {
			if(pulsandodentrodelarea)
		}
	}*/
};

