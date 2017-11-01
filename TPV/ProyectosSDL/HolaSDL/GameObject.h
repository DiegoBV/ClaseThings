#include "Texture.h"
#include "SDL.h"
using namespace std;
#pragma once
class GameObject
{
private:
	Texture* textura = nullptr;
	//Game* game = nullptr;
	SDL_Rect rec_Destino; //posicion del frame en el juego
	
public:
	GameObject();
	~GameObject();
	void crea_GameObject(Texture* text, SDL_Rect rect);
	void render(SDL_Renderer* &renderer);
	void update(SDL_Renderer* &renderer);
};

