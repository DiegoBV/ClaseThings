#pragma once

#include "RenderComponent.h"

class SkeletonRendered : public RenderComponent {
public:
	SkeletonRendered();
	SkeletonRendered(SDL_Color color);
	virtual ~SkeletonRendered();
	void render(GameObject *o, Uint32 time);
private:
	SDL_Color color_;

};

