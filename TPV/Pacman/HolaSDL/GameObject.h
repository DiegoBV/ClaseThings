#pragma once
#include <fstream>
#include <SDL.h>
using namespace std; //CLASE ABSTRACTA, SUS METODOS SON VIRTUALES
class SDLApp;
class GameObject
{
protected:
	SDLApp* app;
	
public:
	GameObject();
	GameObject(SDLApp* app) : app(app) {}
	virtual void render()=0;
	virtual void update()=0; 
	virtual bool handleEvent(SDL_Event& e) = 0;
};

//HERENCIA: GO --> PacmanObject --> Map, GameCharacter
//GO --> Buttons
//GameCharacter --> Pacman, Fantasmas
//Fantasmas --> SmartGhost

