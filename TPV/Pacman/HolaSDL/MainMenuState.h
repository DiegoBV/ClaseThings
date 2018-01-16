#pragma once
#include "GameState.h"
#include "Texture.h"
#include "SDLApp.h"
#include "MenuButton.h"
const int numTexturaMensaje = 6;
class MainMenuState: public GameState
{
private:
	//botones
	Texture* txt;
public:
	MainMenuState();
	~MainMenuState();
	MainMenuState(SDLApp* app, Texture* txt) : txt(txt), GameState(app) {
		stage.push_back(new MenuButton(app->winWidth/2, app->winHeight/2, 50, 50, app->texts[6], app)); //""""""Boton"""""" no funciona vaya
	}
	virtual void render() { this->txt->Render(app->renderer); GameState::render(); }
	void plasmaMensaje();
	virtual void handleEvent(SDL_Event& e);
};

