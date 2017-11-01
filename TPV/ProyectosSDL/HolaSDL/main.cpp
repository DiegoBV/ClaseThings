
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "Texture.h"
#include "GameObject.h"

using namespace std;

SDL_Texture* CreaTexturaIMG(SDL_Renderer* &renderer, string filename){
	SDL_Texture* texture; //Texture
	//string filename = "..\\images\\background1.png";
	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* CreaTexturaBMP(SDL_Renderer* &renderer, string filename){
	SDL_Texture* texture; //Texture
	//string filename = "..\\images\\background1.png";
	SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

SDL_Rect CreaRectangulo(int alturaIMG, int anchuraIMG, int posX, int posY ){
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = anchuraIMG;
	rect.h = alturaIMG;

	return rect;
}

int main(int argc, char* argv[]){
	//Atributes
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int winWidth = 800;
	const int winHeight = 600;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	bool exit = false;
	SDL_Event event;

	//Inicialización del sistema y renderer
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Textures
	int textW1, textH1, textW2, textH2;
	int i = 0;
	int j = 800;
	int h = 800;
	Texture helicopter2;
	helicopter2.CreaTexturaIMG(renderer, "..\\images\\helicopter2.png", 1, 5);
	SDL_Texture* fondo = CreaTexturaIMG(renderer, "..\\images\\background1.png");
	SDL_Texture* perrete = CreaTexturaIMG(renderer, "..\\images\\dog.png");
	SDL_Texture* helicopter = CreaTexturaIMG(renderer, "..\\images\\helicopter.png");
	SDL_QueryTexture(perrete, nullptr, nullptr, &textW1, &textH1);
	SDL_QueryTexture(helicopter, nullptr, nullptr, &textW2, &textH2);
	SDL_Rect destRect1 = CreaRectangulo (100, 100, 0, 400);
	SDL_Rect orRect1 = CreaRectangulo(textH1, textW1 / 6, 0, 0);
	SDL_Rect destRect2 = CreaRectangulo(100, 100, 700, 200);
	SDL_Rect orRect2 = CreaRectangulo(textH2, textW2 / 5, 0, 0);
	SDL_Rect destRect3 = CreaRectangulo(100, 100, 700, 0);
	Texture gatete;
	Texture* punt;
	gatete.CreaTexturaIMG(renderer, "..\\images\\dog.png", 1, 6);
	punt = &gatete;
	GameObject gato;
	gato.crea_GameObject(punt, destRect3);
	if (window == nullptr || renderer == nullptr){
		cout << "Error initializing SDL\n";
	}
	else {
		//Program
		SDL_SetRenderDrawColor(renderer, 0, 0, 172, 255);
		SDL_RenderClear(renderer);
		//Pinta una vez el fondo
		//El perrete camina like a baus
		while (!exit){
			/*gato.update(renderer);
			gato.render(renderer);*/

			orRect1.x = (textW1/6)* int(((SDL_GetTicks() / 100) % 6));
			orRect2.x = (textW2 / 5)* int(((SDL_GetTicks() / 100) % 5));

			if (i >= 800){
				i = 0;
			}

			if (j < 0){
				j = 800;
			}

			if (h < 0){
				h = 800;
			}

			SDL_Delay(5);
			destRect1.x = i;
			destRect2.x = j;
			destRect3.x = h;
			SDL_RenderCopy(renderer, fondo, nullptr, nullptr);
			SDL_RenderCopy(renderer, perrete, &orRect1, &destRect1);
			SDL_RenderCopy(renderer, helicopter, &orRect2, &destRect2);
			helicopter2.Anima(100, renderer, destRect3);
			gato.update(renderer);                // el puntero textura deja de apuntar a la textura wtf...
			gato.render(renderer);
			SDL_RenderPresent(renderer);
			i++;
			j -= 2;
			h--;

			while (SDL_PollEvent(&event) && !exit){
				if (event.type == SDL_QUIT)
					exit = true;
			}
		}

		//Finalization
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return 0;
}