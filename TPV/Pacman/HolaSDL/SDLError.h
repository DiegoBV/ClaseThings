#pragma once
#include "PacManError.h"
#include <stdexcept>
#include <iostream>
using namespace std;

class SDLError: public PacmanError
{
public:
	SDLError(const string& c) : PacmanError(c) {};
	~SDLError();
};

