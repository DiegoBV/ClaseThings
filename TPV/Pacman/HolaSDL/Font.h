#pragma once
#include <SDL_ttf.h>
#include <string>
using namespace std;
class Font
{
private:
	TTF_Font* fuente = nullptr;
public:
	Font();
	Font(string fileName, int size) {
		load(fileName, size);
	}
	~Font() { free(); };
	bool load(string fileName, int size) {
		fuente = TTF_OpenFont(fileName.c_str(), size);
		return fuente != nullptr;
	}
	void free() {
		if (fuente != nullptr) {
			TTF_CloseFont(fuente);
			fuente = nullptr;
		}
	}
	SDL_Surface* generateSurface(string text, SDL_Color color) const{
		return	TTF_RenderText_Solid(fuente, text.c_str(), color);
	}
};

