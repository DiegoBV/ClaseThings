#pragma once

#include "RenderComponent.h"

/*
 *
 */
class PlayersInfoRenderer: public RenderComponent {
public:
	PlayersInfoRenderer();
	virtual ~PlayersInfoRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

