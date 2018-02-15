#include "TimeLimitState.h"
#include "GameOverState.h"
#include "SmartGhost.h"
#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "GameOverState.h"
#include <sstream>

TimeLimitState::~TimeLimitState()
{
}

void TimeLimitState::siguiente_Estado(){
	if (this->win()) { //comrpueba que haya comido todo
		levels_Index++;
		deleteObjects();
		this->carga_Archivo(levels_Index); //carga el siguiente archivo
	}
	else if (pacman->he_Muerto()){
		this->app->getStateMachine()->pushState(new GameOverState(app, app->texts[numTexturaGameOver]));
	}
	else if (counter == timeLim) {
		this->app->getStateMachine()->pushState(new GameOverState(app, app->texts[numTexturaGameOver]));
	}
}