#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "SDLApp.h"
class MenuButton: public GameObject
{
	int x, y, w, h;
	Texture* boton;
	SDL_Rect rect;
	typedef void CallBackOnClick(SDLApp* app);
	CallBackOnClick* cdOnClick;
public:
	MenuButton(int x, int y, int w, int h, Texture * txt, CallBackOnClick* cd,SDLApp* app) : x(x), y(y), w(w), h(h), boton(txt), cdOnClick(cd), GameObject(app) {
		rect.x = x; rect.y = y; rect.h = h; rect.w = w;
	}
	~MenuButton();
	virtual void render() { boton->RenderFrame(app->renderer, rect); };
	virtual void update() {}
	virtual bool handleEvent(SDL_Event& e) {
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			SDL_Point p;
			p.x = e.button.x;
			p.y = e.button.y;
			if (SDL_PointInRect(&p, &rect)) {
				cdOnClick(app);
				return true; //si clickas en el botoin, devuelve true
			}
			else {
				return false; //si clickas en algun lao que no sea el boton, devuelve false
			}
		}
		else {
			return false; //si no hay eventos, devuelve false
		}
	}
};

