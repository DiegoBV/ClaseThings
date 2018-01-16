#pragma once
#include "GameState.h"
#include <stack>
class GameStateMachine
{
private:
	stack <GameState*> states;
public:
	GameStateMachine();
	~GameStateMachine();
	void popState();
	void pushState(GameState* newState);
	GameState* currentState();
	void libera();
};

