#include "SDLApp.h"
#include <exception>


SDLApp::SDLApp()
{
	try {
		window = nullptr;
		renderer = nullptr;
		winWidth = 870;
		winHeight = 644;
		int winX, winY;
		winX = winY = SDL_WINDOWPOS_CENTERED;
		//Inicialización del sistema y renderer
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("First test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		TTF_Init();
		leeTexturas();
		maquinaEstados = new GameStateMachine();
		if (window == nullptr || renderer == nullptr) {
			throw SDLError(SDL_GetError());
		}
	}
	catch (SDLError& e) {
		cout << e.what();
	}
}

void SDLApp::handleEvent() {
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else
			maquinaEstados->currentState()->handleEvent(event);
	}
}

void SDLApp::leeTexturas() {
	ifstream texturas;
	texturas.open(pathInfoTexturas + extTxt); //archivo de texto donde se encuentra la informacion de las diferentes texturas (ruta, filas, columnas, numero de Texturas, etc)
	if (!texturas.is_open()) {
		throw FileNotFoundError("Archivo: " + pathInfoTexturas + extTxt + " no encontrado"); //error de archivo no encontrado
	}
	else {
		int numText = 0;
		texturas >> numText;
		for (int i = 0; i < numText; i++) {
			string fileName;
			int fils, cols;
			texturas >> fileName;
			if (fileName == "Fuente") { //si es la fuente crea una textura vacia y la fuente
				int tamanyo;
				texturas >> fileName >> tamanyo;
				fuente = new Font(fileName, tamanyo);
				texts.push_back(new Texture());
			}
			else {
				texturas >> fils >> cols;
				texts.push_back(new Texture(renderer, fileName, fils, cols));
			}
		}
		for (int i = 0; i < numText; i++) {
			if (texts[i] == nullptr) {
				throw SDLError(IMG_GetError()); //controlar el error de texturas nulas
			}
		}
		texturas.close();
	}
}
