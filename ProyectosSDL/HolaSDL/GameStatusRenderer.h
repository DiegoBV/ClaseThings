#pragma once

#include "RenderComponent.h"

/*
 *
 */
class GameStatusRenderer: public RenderComponent {
public:
	GameStatusRenderer();
	virtual ~GameStatusRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

