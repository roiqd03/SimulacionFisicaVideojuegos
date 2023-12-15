#include "Entity.h"

Entity::Entity(Vector3 size, Vector4 color, float life_time) : size(size), time(0), color(color), life_time(life_time), generator(nullptr), force({ 0,0,0 }) {}

Entity::~Entity() {
	if (generator != nullptr) delete generator;
	if (renderItem != nullptr) renderItem->release();
}

void Entity::integrate(double t) {
	time += t;
	clearAccum();
}

void Entity::setContext(std::list<Entity*>::iterator it2) { it = it2; }
std::list<Entity*>::iterator  Entity::getContext() { return it; }

void Entity::setInvisible() {
	renderItem->release();
	renderItem = nullptr;
}

void Entity::addGenerator(ParticleGenerator* g) {
	if (generator != nullptr) delete generator;
	generator = g;
}
