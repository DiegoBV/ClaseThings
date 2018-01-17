#pragma once
#include "SDL.h"
#include "Texture.h"
#include "GameMap.h"
#include "Ghost.h"
#include "Pacman.h"
#include <vector>
#include <fstream>
#include <list>
#include <SDL_ttf.h>
#include "Font.h"
#include "GameState.h"
#include "SDLApp.h"
#include "GameObject.h"
#include "PauseState.h"
using namespace std;
const int vitaminasTiempo = 30;
const int frameRate = 130;
const string pathTxt = "..\\level0";
const int ptosFantasma = 100;
const int ptosComida = 1;
const int ptosVitamina = 10;
const int r = 255;
const int g = 255; //color
const int b = 255;
const int numFantasmaInteligente = 8; //numero en la textura proporcionada
const SDL_Rect hudScore = { 800, 0, 50, 40 };
const SDL_Rect hudVidas = { 0, 0, 35, 35 };
class Game: public GameState
{
private:
	GameMap* map;
	Pacman* pacman;
	ifstream archivo;
	ofstream partidaGuardada;
	int score = 0;
	list <GameObject*>::reverse_iterator obj;
	SDL_Color color;
	bool vitaminas;
	int vitaminasTiempoAux = 0;
	int numComida = 0; //numero de comida y vitaminas, para ver si se ha ganado o no
	int startTime;
	int frameTime; // mediciones del tiempo para un Delay "eficiente"
	int levels_Index = 1;

public:
	vector<Texture*> texts;
	Game(SDLApp* app, int lvl);
	~Game() { /*deleteObjects();*/ };
	void carga_Archivo(int lvl);
	string nombreFichero(string path, int num, string ext);

	virtual void handleEvent(SDL_Event& e) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				this->app->getStateMachine()->pushState(new PauseState(app, app->texts[numTexturaMenu]));
			}
			else pacman->handleEvent(e);
		}
	}

	void update() {
		comprueba_colisiones(pacman->get_PosActX(), pacman->get_PosActY());
		tiempo_Vitamina();
		GameState::update();
		this->delay();
		siguiente_Estado();
	}
	void render() {
		GameState::render();
		texts[texts.size() - 1]->loadFromText(app->renderer, to_string(score), *(app->fuente), color);
		this->animaciones_Extra();
		texts[texts.size() - 1]->RenderFrame(app->renderer, hudScore);
		plasmaVidas();
	}

	int dame_Altura();
	int dame_Anchura();  //los gets para saber las dimensiones del tablero y pantalla
	int dame_FilasTablero();
	int dame_ColumnasTablero();
	SDL_Renderer* dame_Renderer();
	int obtenerPixelX(int casilla);
	int obtenerPixelY(int casilla);
	void give_posPacman(int &posX, int &posY);
	void nace_Fantasma(int posX, int posY);
	MapCell consulta(int x, int y);
	bool comprueba_colisiones(int x, int y);
	bool siguiente_casilla(int &X, int &Y, int dirX, int dirY);
	void come(int x, int y);
	void setComida(int a);
	void sumaScore(int suma);
	bool colision_Fantasma(int posX, int posY);
	void delay();
	void animaciones_Extra();
	void tiempo_Vitamina();
	void plasmaVidas();
	void siguiente_Estado();
	bool win();
	void deleteObjects();
	bool dameVitamina();
	void save();
	void guarda_Partida(int lvl);
	SDLApp* Game::getApp();

};
/*private:
	bool exit = false; //booleano que indica si se ha salido del juego o no

	//-------------------------------SDL----------------------------

	/*SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event termina;
	Font* fuente;
	SDL_Color color;
	SDL_Event event; //maneja eventos*/

	//-------------------------------Lista/ObjetosGame ----------------------------

	/*list <GameCharacter*>objects; //lista de objetos del juego (fantasmas y pacman)
	list <GameCharacter*>::reverse_iterator ghost; //iterador que va desde el final hasta el principio para recorrer los fantasmas
	list <GameCharacter*>::reverse_iterator ghost2; //Iterador para las colisiones entre fantasmas
	Pacman *pacman;
	GameMap* map;

	//-------------------------------Métodos ----------------------------

	void siguiente_Estado();
	void update();
	void render();
	string nombreFichero(string path, int num, string ext);
	void deleteObjects();
	void pinta_Mapa();
	void handle_Events(); //se encarga de manejar los eventos de teclado para controlar a Pacman
	void run();
	bool win();
	void animaciones_Extra();
	void tiempo_Vitamina();
	void carga_Archivo(int lvl);//carga el archivo
	void guarda_Partida(int lvl);
	void save();
	int escribe_Code();
	void sumaScore(int suma);
	void game_Over();
	void delay();
	void leeTexturas();
	void plasmaMensaje();
	void plasmaVidas();

	//-------------------------------Auxiliares ----------------------------

	ifstream archivo;
	ofstream partidaGuardada;
	int winWidth;
	int winHeight;
	int winX, winY;
	int numComida = 0; //numero de comida y vitaminas, para ver si se ha ganado o no
	int startTime;
	int frameTime; // mediciones del tiempo para un Delay "eficiente"
	bool vitaminas = false;
	int vitaminasTiempoAux = vitaminasTiempo;
	int levels_Index = 1;  //cambiar de nivel al ganar
	bool saveState = false;
	int score = 0;

public:
	Game();
	~Game();
	vector <Texture*> texts;
	void menu();
	bool siguiente_casilla(int &X, int &Y, int dirX, int dirY); //Le pasamos la casilla actual y calcula la siguiente
	void give_posPacman(int &posX, int &posY);
	void come(int x, int y); //cambia casilla de vitamina o de comida a vacia
	MapCell consulta(int x, int y); //devuelve el tipo de casilla que le indicas
	bool comprueba_colisiones(int x, int y);
	void setComida(int a); //suma o resta comida, hecho para sumar o restar de 1 en 1
	int dame_Altura();
	int dame_Anchura();  //los gets para saber las dimensiones del tablero y pantalla
	int dame_FilasTablero();
	int dame_ColumnasTablero();
	bool colision_Fantasma(int posX, int posY);
	void nace_Fantasma(int posX, int posY);
	bool dame_exit();
	SDL_Renderer* dame_Renderer();
	int obtenerPixelX(int casilla);
	int obtenerPixelY(int casilla);
};*/

 
