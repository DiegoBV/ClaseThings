#pragma once
#include "PacmanError.h"
#include <string>
class FileNotFoundError: public PacmanError
{
public:
	FileNotFoundError(const string& c) : PacmanError(c) {};
	~FileNotFoundError();
};

