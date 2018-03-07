#ifndef PADDLEMOUSEINPUTCOMPONENT_H_
#define PADDLEMOUSEINPUTCOMPONENT_H_

#include "InputComponent.h"

/*
 *
 */
class PaddleMouseInputComponent: public InputComponent {
public:
	PaddleMouseInputComponent();
	virtual ~PaddleMouseInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

#endif /* PADDLEMOUSEINPUTCOMPONENT_H_ */
