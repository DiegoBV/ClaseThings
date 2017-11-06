#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::crea_GameObject(Texture* text, const SDL_Rect rect) {
	textura = text;  //si pongo textura  = &text, siendo text una variable tipo Texture no me deja (?), pierde la referencia nu se
	rec_Destino.x = rect.x;
	rec_Destino.h = rect.h;
	rec_Destino.w = rect.w;
	rec_Destino.y = rect.y;
	
}

void GameObject::render(SDL_Renderer* &renderer) { //todos los renderer sobrarian, se cogerian del puntero a Game...
	if(textura != nullptr)
	textura -> Anima(100, renderer, rec_Destino);
}

void GameObject::update(SDL_Renderer* &renderer) {
	if (rec_Destino.x >= 800) {
		rec_Destino.x = 0;
	}
	rec_Destino.x+= 5;

}
