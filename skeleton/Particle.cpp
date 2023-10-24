#include "Particle.h"

Particle::Particle(float r, Vector4 color, float life_time) : vel({0,0,0}), radius(r), ac({ 0,0,0 }),
	gravity({ 0,0,0 }), damping(1), mass(0), time(0), color(color), life_time(life_time), generator(nullptr) {
	
	pose = physx::PxTransform({0,0,0});
	Vector4 c = color;
	physx::PxSphereGeometry sphere(r);
	physx::PxShape* shape = CreateShape(sphere);
	renderItem = new RenderItem(shape, &pose, c);
}

Particle::~Particle() {
	if(generator != nullptr) delete generator;
	if(renderItem != nullptr) renderItem->release();
}

void Particle::integrate(double t) {
	pose.p += vel * t;
	vel = (vel + (ac + gravity) * t) * pow(damping, t);

	time += t;
}

void Particle::setVelocity(Vector3 v) { vel = v; }
void Particle::setPosition(Vector3 p) { pose.p = p; }

void Particle::setMass(float f) { mass = f; }
void Particle::setAcceleration(Vector3 ac) { this->ac = ac; }
void Particle::setDamping(float d) { damping = d; }
void Particle::setGravity(Vector3 g) { gravity = g; }
Particle* Particle::clone() const {
	Particle* _particle = new Particle(radius, color, life_time);

	_particle->pose.p = pose.p;
	_particle->vel = vel;
	_particle->ac = ac;
	_particle->gravity = gravity;
	_particle->mass = mass;
	_particle->damping = damping;

	return _particle;
}


void Particle::setContext(std::list<Particle*>::iterator it2) { it = it2; }
std::list<Particle*>::iterator  Particle::getContext() { return it; }

void Particle::setInvisible() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::addGenerator(ParticleGenerator* g) {
	if (generator != nullptr) delete generator;
	generator = g;
}
