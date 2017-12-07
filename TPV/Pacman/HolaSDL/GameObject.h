#pragma once
class Game;
class GameObject
{
protected:
	Game* game;
	//virtual void render() = 0;
	//virtual void update() = 0;
	//virtual void loadFromFile(ifstream file) = 0;
	//virtual void saveToFile() = 0;
public:
	GameObject();
	~GameObject();
};

