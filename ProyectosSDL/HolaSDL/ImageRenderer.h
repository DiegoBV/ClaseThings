#pragma once

#include "RenderComponent.h"
#include "Texture.h"

class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture* texture);
	ImageRenderer(Texture* texture, SDL_Rect clip);

	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);

private:
	Texture* texture_;
	SDL_Rect clip_;
	Vector2D direction_;
};

