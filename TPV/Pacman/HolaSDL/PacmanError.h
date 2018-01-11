#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

class PacmanError: public logic_error
{
public:
	PacmanError(const string& c) : logic_error("PacmanError " + c) {};
	~PacmanError();
};

