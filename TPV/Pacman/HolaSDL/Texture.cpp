#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture :: CreaTexturaIMG(SDL_Renderer* &renderer, string filename, int fils, int cols){
	//SDL_Texture* texture; //Texture
	//string filename = "..\\images\\background1.png";
	SDL_Surface* surface = IMG_Load(filename.c_str());
	textura = SDL_CreateTextureFromSurface(renderer, surface);
	textH = surface->h;
	textW = surface->w;
	CreaRectangulo(textH/fils, textW/cols, 0, 0);
	SDL_FreeSurface(surface);	
	filas = fils;
	columnas = cols;

}

/*void Texture::CreaTexturaBMP(SDL_Renderer* &renderer, string filename){
	//SDL_Texture* texture; //Texture
	//string filename = "..\\images\\background1.png";
	SDL_Surface* surface = SDL_LoadBMP(filename.c_str());
	textura = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}*/

void Texture::CreaRectangulo(int alturaIMG, int anchuraIMG, int posX, int posY){
	rect.x = posX;
	rect.y = posY;
	rect.w = anchuraIMG;
	rect.h = alturaIMG;
}

void Texture::Render(SDL_Renderer* rnd){
	SDL_RenderCopy(rnd, textura, &rect, nullptr);
}

void Texture::RenderFrame(SDL_Renderer* rnd, const SDL_Rect dest) {
	SDL_RenderCopy(rnd, textura, &rect, &dest);
}

void Texture::Anima(int veloc, SDL_Renderer* rnd, SDL_Rect dest){
	rect.x = (textW / columnas)* int(((SDL_GetTicks() / veloc) % columnas));
	RenderFrame(rnd, dest);
}