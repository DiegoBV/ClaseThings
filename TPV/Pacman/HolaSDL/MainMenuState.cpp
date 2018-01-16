#include "MainMenuState.h"
#include "Game.h"


MainMenuState::MainMenuState()
{
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::handleEvent(SDL_Event& e) {
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		this->app->getStateMachine()->pushState(new Game(app)); //por ahora que no tenemos botones o_O
		//x = e.button.x;
		//y = e.button.y;
		//if (x > rectNew.x && x < rectNew.x + rectNew.w && y > rectNew.y && y < rectNew.y + rectNew.h) {
			//this->carga_Archivo(1);
			//finish = true;
		//}
		/*else if (x > rectLoad.x && x < rectLoad.x + rectLoad.w && y > rectLoad.y && y < rectLoad.y + rectLoad.h) {
			saveState = true;
			plasmaMensaje();
			int code = this->escribe_Code();
			this->carga_Archivo(code);
			finish = true;*/
		}
}

void MainMenuState::plasmaMensaje() {
	SDL_Rect r = { this->app->winHeight / 3 - 50, this->app->winWidth / 4, 400, 200 };
	app->texts[numTexturaMensaje]->RenderFrame(app->renderer, r);
	SDL_RenderPresent(app->renderer);
}
