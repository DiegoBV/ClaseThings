#ifndef GAMECTRLINPUTCOMPONENT_H_
#define GAMECTRLINPUTCOMPONENT_H_

#include "InputComponent.h"

/*
 *
 */
class GameCtrlInputComponent: public InputComponent {
public:
	GameCtrlInputComponent();
	virtual ~GameCtrlInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

#endif /* GAMECTRLINPUTCOMPONENT_H_ */
