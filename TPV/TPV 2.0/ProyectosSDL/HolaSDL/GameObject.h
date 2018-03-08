#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "SDLGame.h"
#include "Vector2D.h"

class GameObject {

public:
	GameObject(SDLGame* game);
	virtual ~GameObject();

	SDLGame* getGame() const;

	bool isActive() const;
	void setActive(bool active);
	bool toggleActive();

	double getWidth() const;
	void setWidth(double width);
	double getHeight() const;
	void setHeight(double height);
	void scale(double s);

	const Vector2D& getPosition() const;
	void setPosition(const Vector2D &pos);

	const Vector2D& getVelocity() const;
	void setVelocity(const Vector2D &vel);

	const Vector2D& getDirection() const;
	void setDirection(const Vector2D &vel);

	// abstract methods to be implemented in sub-classes
	virtual void handleInput(Uint32 time, const SDL_Event& event) = 0;
	virtual void update(Uint32 time) = 0;
	virtual void render(Uint32 time) = 0;

protected:
	SDLGame* game_; // pointer to the game

	bool active_;   // indicates if the object is active

	double width_;  // width
	double height_; // height

	Vector2D position_; // position
	Vector2D direction_; // angle in degrees (0) is considered facing left
	Vector2D velocity_; // direction


};

#endif /* GAMEOBJECT_H_ */
