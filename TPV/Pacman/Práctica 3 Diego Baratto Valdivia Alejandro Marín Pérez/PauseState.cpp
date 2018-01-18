#include "PauseState.h"
#include "Game.h"



PauseState::PauseState()
{
}


PauseState::~PauseState()
{
}

void PauseState::save(SDLApp* app) {
	app->getStateMachine()->popState(); 
	static_cast<Game*> (app->getStateMachine()->currentState())->save();
}