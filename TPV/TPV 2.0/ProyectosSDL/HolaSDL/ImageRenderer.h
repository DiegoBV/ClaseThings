#ifndef IMAGERENDERER_H_
#define IMAGERENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class ImageRenderer: public RenderComponent {
public:
	ImageRenderer(Texture* image, SDL_Rect clip);
	ImageRenderer(Texture* image);
	virtual ~ImageRenderer();
	virtual void render(GameObject* o, Uint32 time);
	double angle(GameObject* o);
private:
	SDL_Rect clip_;
	Vector2D origDir;
	Texture* image_;
};

#endif /* IMAGERENDERER_H_ */
