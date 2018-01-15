#pragma once
#include "GameObject.h"
#include "Texture.h"
class MenuButton: public GameObject
{
	Texture* boton;
public:
	MenuButton();
	~MenuButton();
	MenuButton(Texture* txt);
	virtual void render();
	//virtual void update();
	//virtual bool handleEvent(SDL_Event& e);
};

