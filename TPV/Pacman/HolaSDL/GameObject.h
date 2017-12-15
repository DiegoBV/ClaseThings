#pragma once
#include <fstream>
#include "Game.h"
using namespace std;

class GameObject
{
protected:
	Game* game;
	
public:
	GameObject();
	~GameObject();
	virtual void render()=0;
	virtual void render(bool)=0;
	virtual void update()=0;
	virtual void loadFromFile(ifstream& file)=0;
	//virtual void saveToFile()=0;
};

