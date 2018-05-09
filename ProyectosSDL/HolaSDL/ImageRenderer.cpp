#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* texture) :
		texture_(texture), clip_(
				{ 0, 0, texture->getWidth(), texture->getHeight() }) {
	direction_ = Vector2D(0, -1);
}

ImageRenderer::ImageRenderer(Texture* texture, SDL_Rect clip) :
		texture_(texture), clip_(clip) {
	direction_ = Vector2D(0, -1);
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	if (texture_) {
		SDL_Rect dest { static_cast<int>(o->getPosition().getX()),
				static_cast<int>(o->getPosition().getY()),
				static_cast<int>(o->getWidth()),
				static_cast<int>(o->getHeight()) };
		texture_->render(o->getGame()->getRenderer(), dest,
				static_cast<int>(-o->getDirection().angle(direction_)), &clip_);
	}
}

