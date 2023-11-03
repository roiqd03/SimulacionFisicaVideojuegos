#include "Particle.h"

Particle::Particle(float r, Vector4 color, float life_time) : vel({0,0,0}), radius(r), ac({ 0,0,0 }),
	damping(1), inv_mass(0), time(0), color(color), life_time(life_time), generator(nullptr), force({0,0,0}) {
	
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
	ac = force * inv_mass;
	vel += ac * t;
	vel *= powf(damping, t);
	pose.p += vel * t;
	
	time += t;
	clearAccum();
}

void Particle::setVelocity(Vector3 v) { vel = v; }
void Particle::setPosition(Vector3 p) { pose.p = p; }

void Particle::setAcceleration(Vector3 ac) { this->ac = ac; }
void Particle::setDamping(float d) { damping = d; }
//void Particle::setGravity(Vector3 g) { gravity = g; }
Particle* Particle::clone() const {
	Particle* _particle = new Particle(radius, color, life_time);

	_particle->pose.p = pose.p;
	_particle->vel = vel;
	_particle->ac = ac;
	//_particle->gravity = gravity;
	_particle->inv_mass = inv_mass;
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
