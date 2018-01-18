#pragma once
#include "GameStateMachine.h"
#include "Font.h"
#include "FileNotFoundError.h"
#include <vector>
#include "Texture.h"
const string pathInfoTexturas = "..\\infoTexturas";
const string extTxt = ".pac";
const int numTexturaMensaje = 6;
const int numTexturaMenu = 4;
const int numTexturaGameOver = 5;
const int numTexturaResume = 10;
const int numTexturaQuit = 11;
const int numTexturaSave = 12;
const int anchura = 400; //de los botones y eso
const int altura = 100;
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
	void libera() { maquinaEstados->libera(); for (int i = 0; i < texts.size(); i++) delete texts[i]; SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); TTF_Quit(); }
	void setExit(bool b) { exit = b; }
	int SDLApp::escribe_Code();
	void plasmaMensaje();
};

