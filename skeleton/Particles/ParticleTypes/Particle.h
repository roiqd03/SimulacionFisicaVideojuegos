#pragma once
#include "../../RenderUtils.hpp"
#include "../ParticleGenerators/ParticleGenerator.h"
#include <list>

class Particle
{
public:
	Particle(float radius, Vector4 color, float life_time);
	Particle(Vector3 size, Vector4 color, float life_time);
	virtual ~Particle();
	virtual void integrate(double t);
	void setVelocity(Vector3 v);
	void setPosition(Vector3 p);
	inline void setInvMass(float _inv_mass) { 
		inv_mass = _inv_mass; 
		if (inv_mass != 0)
			density = 1 / inv_mass / volume;
		else density = 0;
	}
	void setAcceleration(Vector3 ac);
	void setGravity(Vector3 g);
	void setDamping(float d);
	inline Vector3 getVelocity() { return vel; }
	inline Vector3 getPosition() { return pose.p; }
	inline Vector3 setAcceleration() { return ac; }
	//inline Vector3 setGravity() { return gravity; }
	inline float setDamping() { return damping; }
	inline float getVolume() { return volume; }
	inline float getDensity() { return density; }
	inline float getTime() { return time; }
	inline float getInvMass() { return inv_mass; }
	inline float getLifeTime() { return life_time; }
	inline Vector3 getSize() { return size; }
	inline Vector4 getColor() { return color; }
	inline void setLifeTime(float life_time) { this->life_time = life_time; }
	void setInvisible();
	void setFirstGenerator(ParticleGenerator* myG) { firstGenerator = myG; };
	void setContext(std::list<Particle*>::iterator);
	std::list<Particle*>::iterator getContext();
	virtual Particle* clone() const;
	inline bool generatesOnDeath() { return generator != nullptr; }
	inline std::pair<std::list<Particle*>, ParticleGenerator*> generateParticles() { generator->changePosition(pose.p);  return { generator->generateParticles(), generator }; }
	void addGenerator(ParticleGenerator* g);
	virtual void onDeath(){};

	Vector3 force;
	void clearForce();
	void addForce(const Vector3& f) { force += f; }
	void clearAccum() { force = Vector3(0, 0, 0); }


	//METODOS DE PRUEBA
	void setVolume(float k) { volume = k; }
protected:
	std::list<Particle*>::iterator it;
	Vector3 ac;
	float inv_mass;
	float damping;
	Vector3 size;
	Vector4 color;
	float time;
	float life_time;
	float volume;
	float density;
	//Vector3 gravity;
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	ParticleGenerator* generator = nullptr;
	ParticleGenerator* firstGenerator = nullptr;
};

