#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::popState() {
	if (!states.empty()) { //si la pila de estados no está vacia
		delete states.top(); //delete y pop
		states.pop();
	}
}

void GameStateMachine::pushState(GameState* newState) {
	states.push(newState); //pushea un nuevo estado a la pila
}

GameState* GameStateMachine::currentState() {
	if (!states.empty()) {
		return states.top(); //return del current state, util para SDLApp
	}
}

void GameStateMachine::libera() {
	while (!states.empty()) {
		popState(); //mientras la pila esté llena, va liberando
	}
}
