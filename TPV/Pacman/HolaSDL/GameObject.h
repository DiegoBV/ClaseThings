#pragma once
#include <fstream>
using namespace std;
class Game;
class GameObject
{
protected:
	Game* game;
	
public:
	GameObject();
	~GameObject();
	virtual void render();
	virtual void render(bool);
	virtual void update();
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile();
};

