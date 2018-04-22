#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image) : image_(image) {
	origDir.setX(0);
	origDir.setY(-1);
}


ImageRenderer::ImageRenderer(Texture* image, SDL_Rect clip) : image_(image), clip_(clip) {
	origDir.setX(0);
	origDir.setY(-1);
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect
			RECT(o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight());
	image_->render(o->getGame()->getRenderer(), rect, angle(o), &clip_);
	//image_->render(o->getGame()->getRenderer(), rect);

/*
	SDL_SetRenderDrawColor(o->getGame()->getRenderer(), COLOR(0xff1111ff));
	SDL_RenderFillRect(o->getGame()->getRenderer(), &rect);
*/
}

double ImageRenderer::angle(GameObject* o){
	Vector2D dir = o->getDirection(); //Vector de dirección actual

	return dir.angle(origDir);
}

void ImageRenderer::setTexture(Texture * image)
{
	this->image_ = image;
}