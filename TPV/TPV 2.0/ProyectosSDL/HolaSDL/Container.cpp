#include "Container.h"

Container::Container(SDLGame* game) :
		GameObject(game), inputComp_(), physicsComp_(), renderComp_() {
}

Container::~Container() {
	/*for (InputComponent* ic : inputComp_) {
		delete ic;
		
	}
	for (RenderComponent* rc : renderComp_) {
		delete rc;
		rc = inputComp_.erase(ic);
	}
	for (InputComponent* ic : inputComp_) {
		delete ic;
		ic = inputComp_.erase(ic);
	}*/
}

void Container::handleInput(Uint32 time, const SDL_Event& event) {
	for (InputComponent* ic : inputComp_) {
		ic->handleInput(this, time, event);
	}
}

void Container::update(Uint32 time) {
	for (PhysicsComponent* pc : physicsComp_) {
		pc->update(this, time);
	}
}

void Container::render(Uint32 time) {
	for (RenderComponent* rc : renderComp_) {
		rc->render(this, time);
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
