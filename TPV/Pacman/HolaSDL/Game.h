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
using namespace std;
const int vitaminasTiempo = 30;
const int frameRate = 120;
const string path = "..\\images\\textura";
const string pathTxt = "..\\level0";
const string extTxt = ".pac";
const int ptosFantasma = 100;
const int ptosComida = 1;
const int ptosVitamina = 10;
const int r = 255;
const int g = 255; //color
const int b = 255;
class Game
{
private:
	bool exit = false; //booleano que indica si se ha salido del juego o no

	//-------------------------------SDL----------------------------
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event termina;
	Font* fuente;
	SDL_Color color;
	SDL_Rect hudScore;
	SDL_Event event; //maneja eventos

	//-------------------------------Lista/ObjetosGame ----------------------------
	list <GameCharacter*>objects; //lista de objetos del juego (fantasmas y pacman)
	list<GameCharacter*>::reverse_iterator ghost; //iterador que va desde el final hasta el principio para recorrer los fantasmas
	Pacman *pacman; //variable auxiliar para controlar al pacman (duda que tngo que preguntarle al profe)
	Texture* texts[7];
	GameMap* map;

	//-------------------------------Métodos ----------------------------
	void siguiente_Estado();
	void update();
	void render();
	string nombreFichero(string path, int num, string ext);
	void deleteObjects();

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
	int filasTablero, colsTablero;
	
	void pinta_Mapa();
	void handle_Events(); //se encarga de manejar los eventos de teclado para controlar a Pacman
	void run();
	bool siguiente_casilla(int &X, int &Y, int dirX, int dirY); //Le pasamos la casilla actual y calcula la siguiente
	void come(int x, int y); //cambia casilla de vitamina o de comida a vacia
	MapCell consulta(int x, int y); //devuelve el tipo de casilla que le indicas
	void setComida(int a); //suma o resta comida, hecho para sumar o restar de 1 en 1
	bool win();
	void animaciones_Extra();
	bool comprueba_colisiones(int x, int y);
	void tiempo_Vitamina();
	void menu();
	void carga_Archivo(int lvl);//carga el archivo
	void guarda_Partida(int lvl);
	void save();
	int escribe_Code();
	void sumaScore(int suma);
	void game_Over();
	int dame_Altura();
	int dame_Anchura();  //los gets para saber las dimensiones del tablero y pantalla
	int dame_FilasTablero();
	int dame_ColumnasTablero();
	bool dame_exit();
	SDL_Renderer* dame_Renderer();
	int obtenerPixelX(int casilla);
	int obtenerPixelY(int casilla);
	void delay();

};

 
