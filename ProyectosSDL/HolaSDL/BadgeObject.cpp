#include "BadgeObject.h"



BadgeObject::BadgeObject()
{
}

BadgeObject::BadgeObject(SDLGame * game): Container(game)
{
	this->setActive(true);
	rend = ImageRenderer(game->getResources()->getImageTexture(Resources::Pistola), rect);
	this->setWidth(50);
	this->setHeight(50);
	this->setPosition(Vector2D(0 , 0 + this->getHeight()/2));
}


BadgeObject::~BadgeObject()
{
}

void BadgeObject::receive(Message * msg){
	switch (msg->id_)
	{
	case BADGE_ON:
		if (!renderAdd) {
			this->addRenderComponent(&rend);
			renderAdd = true; //evita que se añadan muchos
		}
		break;
	case BADGE_OFF:
		this->delRenderComponent(&rend);
		renderAdd = false;
		break;
	default:
		break;
	}
}
