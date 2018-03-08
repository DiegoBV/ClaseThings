#ifndef Container_H_
#define Container_H_

#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include <vector>

using namespace std;
/*
 *
 */
class Container: public GameObject {
public:
	Container() {};
	Container(SDLGame* game);
	virtual ~Container();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual void addInputComponent(InputComponent* ic);
	virtual void addPhysicsComponent(PhysicsComponent* pc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delPhysicsComponent(PhysicsComponent* pc);
	virtual void delRenderComponent(RenderComponent* rc);
	void setGame(SDLGame* newGame) { game_ = newGame; }

private:
	vector<InputComponent*> inputComp_;
	vector<PhysicsComponent*> physicsComp_;
	vector<RenderComponent*> renderComp_;
};

#endif /* Container_H_ */
