#include "Texture.h"


Texture::Texture(SDL_Renderer* &renderer, string filename, int fils, int cols)
{
	this->filas = fils;
	this->columnas = cols;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	textura = SDL_CreateTextureFromSurface(renderer, surface);
	textH = surface->h;
	textW = surface->w;
	rect.w = textW / columnas;
	rect.h = textH / filas;
	SDL_FreeSurface(surface);
}


Texture::~Texture()
{
}

void Texture::ModificaRectangulo(int fil, int col){  //modifica el rect origen, sirve para una textura con multiples sprites y para animar
	rect.x = (textW / columnas) * col;
	rect.y = (textH / filas) * fil;
}

void Texture::Render(SDL_Renderer* rnd){
	SDL_RenderCopy(rnd, textura, &rect, nullptr);
}

void Texture::RenderFrame(SDL_Renderer* rnd, const SDL_Rect dest) {
		SDL_RenderCopy(rnd, textura, &rect, &dest);
}

void Texture::Anima(int veloc, int posInicialX, int posInicialY, int fil, int col){
	this->ModificaRectangulo(posInicialX + int(((SDL_GetTicks() / veloc) % fil)), posInicialY + int(((SDL_GetTicks() / veloc) % col)));
	//utiliza el método ModificaRecángulo, le pasa los parámetros pos inicialX y posInicialY (la pos desde la cual empieza en la textura,
	//usa el método que vimos para animar (lo de los ticks/velocidad y le hace el % con el numero de filas y columnas que tienen los frames de tu textura
	//por ejemplo, en la imagen que tenemos del pacman empieza siempre en la posInicial = 10 y varía la posInicialX, mientras que, como solo hay dos frames
	//tiene 1 fila de frames y dos columnas (no sé si se entiende o_O)
}

bool Texture::loadFromText(SDL_Renderer* renderer, string text, const Font& font, SDL_Color color) {
	SDL_Surface* textSurf = font.generateSurface(text, color);
	if (textSurf == nullptr) {
		cout << "No esta el archivo";
	}
	else {
		textura = SDL_CreateTextureFromSurface(renderer, textSurf);
		if (textura == nullptr) {
			cout << "Error";
			textH = textW = 0;
		}
		else {
			textH = textSurf->h;
			textW = textSurf->w;
			rect.w = textW / columnas;
			rect.h = textH / filas;
		}
		SDL_FreeSurface(textSurf);
	}
	return textura != nullptr;
}