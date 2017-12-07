#pragma once
#include "SDL.h"
#include "Texture.h"
#include "GameMap.h"
#include "Ghost.h"
#include "Pacman.h"
#include <fstream>
using namespace std;
class Game
{
private:
	bool exit = false; //booleano que indica si se ha salido del juego o no
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event termina;
	ifstream archivo;
	ofstream partidaGuardada;
	int winWidth;
	int winHeight;
	int winX, winY;
	int numComida = 0; //numero de comida y vitaminas, para ver si se ha ganado o no
	Texture* texts[6];
	GameMap* map;
	Ghost fantasmas [4]; //array de fantasma, se crean dichos objetos
	Pacman pacman; //GameObject Pacman
	SDL_Event event; //maneja eventos
	int startTime;
	int frameTime; // mediciones del tiempo para un Delay "eficiente"
	int frameRate;
	string path; //path de las texturas
	bool vitaminas = false;
	int vitaminasTiempo = 0;
	string levels[6];
	int levels_Index = 1;  //cambiar de nivel al ganar
	void siguiente_Estado();
	void update();
	void render();

public:
	Game();
	~Game();
	int filasTablero, colsTablero;
	void carga_Archivo(string name);//carga el archivo
	void pinta_Mapa();
	void handle_Events(); //se encarga de manejar los eventos de teclado para controlar a Pacman
	void run();
	bool siguiente_casilla(int &X, int &Y, int dirX, int dirY); //Le pasamos la casilla actual y calcula la siguiente
	void come(int x, int y); //cambia casilla de vitamina o de comida a vacia
	MapCell consulta(int x, int y); //devuelve el tipo de casilla que le indicas
	void setComida(int a); //suma o resta comida, hecho para sumar o restar de 1 en 1
	bool win();
	int dame_Altura();
	int dame_Anchura();  //los gets para saber las dimensiones del tablero y pantalla
	int dame_FilasTablero();
	int dame_ColumnasTablero();
	bool dame_exit();
	void delay();
	SDL_Renderer* dame_Renderer();
	void animaciones_Extra();
	int obtenerPixelX(int casilla);
	int obtenerPixelY(int casilla);
	bool comprueba_colisiones(int x, int y);
	void tiempo_Vitamina();
	void menu();
	void guarda_Partida();
	void game_Over();
};

 
