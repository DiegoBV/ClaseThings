#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture :: CreaTexturaIMG(SDL_Renderer* &renderer, string filename, int fils, int cols){
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
	//rect.x = (textW / columnas)* int(((SDL_GetTicks() / veloc) % numFrames));
	//RenderFrame(rnd, dest);
	this->ModificaRectangulo(posInicialX + int(((SDL_GetTicks() / veloc) % fil)), posInicialY + int(((SDL_GetTicks() / veloc) % col)));
}