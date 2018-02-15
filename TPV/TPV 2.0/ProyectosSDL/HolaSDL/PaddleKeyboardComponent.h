#ifndef PADDLEKEYBOARDCOMPONENT_H_
#define PADDLEKEYBOARDCOMPONENT_H_

#include "InputComponent.h"

/*
 *
 */
class PaddleKeyboardComponent: public InputComponent {
public:
	PaddleKeyboardComponent(SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~PaddleKeyboardComponent();
	virtual void handleInput(GameObject* o, Uint32 time,
			const SDL_Event& event);
private:
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode stop_;
};

#endif /* PADDLEKEYBOARDCOMPONENT_H_ */
