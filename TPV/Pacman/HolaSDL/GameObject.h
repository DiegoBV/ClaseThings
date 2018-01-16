#pragma once
#include <fstream>
#include <SDL.h>
using namespace std;
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

