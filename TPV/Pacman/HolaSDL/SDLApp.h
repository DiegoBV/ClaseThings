#pragma once
#include "GameStateMachine.h"
#include "Font.h"
#include "FileNotFoundError.h"
#include <vector>
#include "Texture.h"
const string pathInfoTexturas = "..\\infoTexturas";
const string extTxt = ".pac";
class SDLApp
{
private:
	GameStateMachine* maquinaEstados;
	//-------------------------------SDL----------------------------

	SDL_Window* window;
	//SDL_Event termina;
	
	SDL_Color color;
	SDL_Event event; //maneja eventos
	bool exit = false;
	void leeTexturas();

public:
	Font* fuente;
	vector <Texture*> texts;
	SDL_Renderer* renderer;
	int winWidth;
	int winHeight;
	SDLApp();
	~SDLApp() { this->libera(); };
	GameStateMachine* getStateMachine() { return this->maquinaEstados; }
	void update() { maquinaEstados->currentState()->update(); }
	void render() { SDL_RenderClear(renderer); maquinaEstados->currentState()->render(); SDL_RenderPresent(renderer); }
	void handleEvent();
	void run() { while (!this->exit) { handleEvent(); update(); render(); } }
	void libera() { for (int i = 0; i < texts.size(); i++) delete texts[i]; SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); TTF_Quit(); }
	void setExit(bool b) { exit = b; }
};

