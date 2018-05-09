#pragma once

#include "RenderComponent.h"

/*
 *
 */
class ConnectedPlayersRenderer: public RenderComponent {
public:
	ConnectedPlayersRenderer();
	virtual ~ConnectedPlayersRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

