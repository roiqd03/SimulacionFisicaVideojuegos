#include "Particle.h"

Particle::Particle(Vector3 size, Vector4 color, float life_time) : Entity(size, color, life_time), vel({0,0,0}), ac({ 0,0,0 }),
	damping(1), inv_mass(0){
	
	sphereShape = false;
	pose = physx::PxTransform({0,0,0});
	Vector4 c = color;
	physx::PxShape* shape;
	volume = size.x * size.y * size.z;
	physx::PxBoxGeometry cube(size / 2);
	shape = CreateShape(cube);
	
	renderItem = new RenderItem(shape, &pose, c);
}

Particle::Particle(float radius, Vector4 color, float life_time) : Entity({ radius,radius,radius }, color, life_time), vel({ 0,0,0 }), ac({ 0,0,0 }),
damping(1), inv_mass(0) {

	sphereShape = true;
	pose = physx::PxTransform({ 0,0,0 });
	Vector4 c = color;
	physx::PxShape* shape;
	volume = (4.0f / 3.0f) * atan(1) * 4 * pow(radius, 3);
	physx::PxSphereGeometry sphere(radius);
	shape = CreateShape(sphere);

	renderItem = new RenderItem(shape, &pose, c);
}


Particle::~Particle() {}

void Particle::integrate(double t) {
	ac = force * inv_mass;
	vel += ac * t;
	vel *= powf(damping, t);
	pose.p += vel * t;

	Entity::integrate(t);
}

void Particle::setVelocity(Vector3 v) { vel = v; }
void Particle::setPosition(Vector3 p) { pose.p = p; }

void Particle::setAcceleration(Vector3 ac) { this->ac = ac; }
void Particle::setDamping(float d) { damping = d; }
Entity* Particle::clone() const {
	Particle* _particle;
	if (sphereShape)
		_particle = new Particle(size.x, color, life_time);
	else
		_particle = new Particle(size, color, life_time);
	
	_particle->pose.p = pose.p;
	_particle->vel = vel;
	_particle->ac = ac;
	_particle->inv_mass = inv_mass;
	_particle->damping = damping;
	_particle->firstGenerator = firstGenerator;

	return _particle;
}