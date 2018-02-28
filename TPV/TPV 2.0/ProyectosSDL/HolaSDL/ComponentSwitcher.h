#ifndef COMPONENTSWITCHER_H_
#define COMPONENTSWITCHER_H_

#include "GameObject.h"
#include "Container.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include <vector>

/*
 *
 */
class ComponentSwitcher: public GameObject {
public:

	struct ModeInfo {
		InputComponent* ic;
		PhysicsComponent* pc;
		RenderComponent* rc;
		RenderComponent* iconRC;
	};

	ComponentSwitcher(SDLGame* game, Container* o, SDL_Keycode key);
	virtual ~ComponentSwitcher();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	void addMode(ModeInfo mode);
	void switchToNextMode();
	void setMode(int i);

private:
	Container* o_;
	SDL_Keycode key_;
	std::vector<ModeInfo> modes_;
	int currMode_;
};

#endif /* COMPONENTSWITCHER_H_ */
