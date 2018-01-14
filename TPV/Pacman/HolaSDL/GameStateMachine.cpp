#include "GameStateMachine.h"



GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::popState() {
	if (!states.empty()) { //si la pila de estados no está vacia
		delete states.top();
		states.pop();
	}
}

void GameStateMachine::pushState(GameState* newState) {
	states.push(newState);
}

GameState* GameStateMachine::currentState() {
	if (!states.empty()) {
		return states.top();
	}
}
