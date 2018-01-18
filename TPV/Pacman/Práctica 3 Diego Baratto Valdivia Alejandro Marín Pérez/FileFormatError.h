#pragma once
#include "PacmanError.h"
class FileFormatError : public PacmanError
{
public:
	FileFormatError(const string& c) : PacmanError(c) {};
	~FileFormatError();
};

