#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDLApp.h"
class MenuButton: public GameObject
{
	int x, y, w, h;
	Texture* boton;
	SDL_Rect rect;
public:
	MenuButton(int x, int y, int w, int h, Texture * txt, SDLApp* app) : x(x), y(y), w(w), h(h), boton(txt), GameObject(app) {
		rect.x = x; rect.y = y; rect.h = h; rect.w = w;
	}
	~MenuButton();
	virtual void render() { boton->RenderFrame(app->renderer, rect); };
	virtual void update() {}
	virtual bool handleEvent(SDL_Event& e) { return false; }
	/*virtual bool handleEvent(SDL_Event& e) {
		if (...ratonPulsado) {
			if(pulsandodentrodelarea)
		}
	}*/
};

