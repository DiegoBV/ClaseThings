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
	this->setPosition(Vector2D(0 , 0 + this->getHeight()));
}


BadgeObject::~BadgeObject()
{
}

void BadgeObject::receive(Message * msg){
	switch (msg->id_)
	{
	case BADGE_ON:
		if (!renderAdd) {
			changeTexture();
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

void BadgeObject::changeTexture()
{
	switch (indexEnum) {
	case 0:
		this->rend.setTexture(game_->getResources()->getImageTexture(Resources::Pistola));
		indexEnum++;
		break;
	case 1:
		this->rend.setTexture(game_->getResources()->getImageTexture(Resources::Escudo));
		indexEnum++;
		break;
	case 2:
		this->rend.setTexture(game_->getResources()->getImageTexture(Resources::MultiShot));
		indexEnum = 0;
		break;
	}
	//this->rend.setTexture(im);
}
