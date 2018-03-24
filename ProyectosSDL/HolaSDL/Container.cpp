#include "Container.h"

Container::Container(SDLGame* game) :
		GameObject(game), inputComp_(), physicsComp_(), renderComp_() {
}

Container::~Container() {
}

void Container::handleInput(Uint32 time, const SDL_Event& event) {
	if (this->isActive()) {
		for (InputComponent* ic : inputComp_) {
			ic->handleInput(this, time, event);
		}
	}
}

void Container::update(Uint32 time) {
	if (this->isActive()) {
		for (PhysicsComponent* pc : physicsComp_) {
			pc->update(this, time);
		}
	}
}

void Container::render(Uint32 time) {
	if (this->isActive()) {
		for (RenderComponent* rc : renderComp_) {
			rc->render(this, time);
		}
	}
}

void Container::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void Container::addPhysicsComponent(PhysicsComponent* pc) {
	physicsComp_.push_back(pc);
}

void Container::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

void Container::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
			inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void Container::delPhysicsComponent(PhysicsComponent* pc) {
	std::vector<PhysicsComponent*>::iterator position = std::find(
			physicsComp_.begin(), physicsComp_.end(), pc);
	if (position != physicsComp_.end())
		physicsComp_.erase(position);
}

void Container::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
			renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}
