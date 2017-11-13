#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture :: CreaTexturaIMG(SDL_Renderer* &renderer, string filename, int fils, int cols, int fila_Inicio, int col_Inicio){
	//SDL_Texture* texture; //Texture
	//string filename = "..\\images\\background1.png";
	this->filas = fils;
	this->columnas = cols;
	SDL_Surface* surface = IMG_Load(filename.c_str());
	textura = SDL_CreateTextureFromSurface(renderer, surface);
	textH = surface->h;
	textW = surface->w;
	ModificaRectangulo((textW/columnas) * col_Inicio, (textH/filas) * fila_Inicio);//para las imágenes con varias texturas
	rect.w = textW / columnas;
	rect.h = textH / filas;
	SDL_FreeSurface(surface);	
}

/*void Texture::CreaTexturaBMP(SDL_Renderer* &renderer, string filename){
	//SDL_Texture* texture; //Texture
	//string filename = "..\\images\\background1.png";
	SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
	textura = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}*/

void Texture::ModificaRectangulo(int fil, int col){  //modifica el rect origen, sirve para una textura con multiples sprites
	rect.x = (textW / columnas) * col;
	rect.y = (textH / filas) * fil;
}

void Texture::Render(SDL_Renderer* rnd, SDL_Rect dest){
	SDL_RenderCopy(rnd, textura, &rect, &dest);
}

void Texture::RenderFrame(SDL_Renderer* rnd, const SDL_Rect dest) {
	SDL_RenderCopy(rnd, textura, &rect, &dest);
}

void Texture::Anima(int veloc, SDL_Renderer* rnd, SDL_Rect dest){
	rect.x = (textW / columnas)* int(((SDL_GetTicks() / veloc) % columnas));
	RenderFrame(rnd, dest);
}