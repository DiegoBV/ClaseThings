#pragma once
#include "RenderComponent.h"
class LiveRenderer :
	public RenderComponent
{
public:
	LiveRenderer();
	virtual ~LiveRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

