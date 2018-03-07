#include "GameObject.h"

GameObject::GameObject(SDLGame* game) :
		game_(game), active_(true), width_(), height_(), position_(),  direction_(1,0), velocity_() {
}

GameObject::~GameObject() {
}

SDLGame* GameObject::getGame() const {
	return game_;
}

bool GameObject::isActive() const {
	return active_;
}
void GameObject::setActive(bool active) {
	active_ = active;
}

bool GameObject::toggleActive() {
	active_ = !active_;
	return active_;
}

double GameObject::getWidth() const {
	return width_;
}

void GameObject::setWidth(double width) {
	width_ = width;
}

double GameObject::getHeight() const {
	return height_;
}

void GameObject::setHeight(double height) {
	height_ = height;
}

const Vector2D& GameObject::getPosition() const {
	return position_;
}

void GameObject::setPosition(const Vector2D &pos) {
	position_.set(pos);
}

const Vector2D& GameObject::getVelocity() const {
	return velocity_;
}

void GameObject::setVelocity(const Vector2D &vel) {
	velocity_.set(vel);
}

const Vector2D& GameObject::getDirection() const {
	return direction_;
}

void GameObject::scale(double s) {
	width_ *= s;
	height_ *= s;
}

void GameObject::setDirection(const Vector2D &vel) {
	direction_.set(vel);
	direction_.normalize();
}

