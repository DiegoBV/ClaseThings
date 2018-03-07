#ifndef DEMOACTOR_H_
#define DEMOACTOR_H_

#include "GameObject.h"

/*
 *
 */
class DemoActor: public GameObject {
public:
	DemoActor(SDLGame* game);
	virtual ~DemoActor();

	virtual void handleInput(Uint32 time, const SDL_Event& event) ;
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

};

#endif /* DEMOACTOR_H_ */
