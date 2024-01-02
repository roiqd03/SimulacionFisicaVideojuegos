#pragma once
#include "../../RenderUtils.hpp"
#include "../Generators/ParticleGenerator.h"
#include "Entity.h"
#include <list>

class RigidSolid : public Entity
{
public:
	RigidSolid(float radius, Vector4 color, float life_time, bool isStatic, physx::PxPhysics* physics, physx::PxScene* scene);
	RigidSolid(Vector3 size, Vector4 color, float life_time, bool isStatic, physx::PxPhysics* physics, physx::PxScene* scene);
	virtual ~RigidSolid();
	virtual void integrate(double t);
	virtual void setVelocity(Vector3 v);
	virtual void setPosition(Vector3 p);
	virtual inline void setInvMass(float _inv_mass) {
		if (!isStatic) physx::PxRigidBodyExt::updateMassAndInertia(*rb, physx::PxReal(1.0f / _inv_mass / volume));
		Entity::setInvMass(_inv_mass);
	}
	virtual void setAcceleration(Vector3 ac){};
	virtual inline Vector3 getVelocity() { if (!isStatic) return rb->getLinearVelocity(); else return { 0, 0, 0 }; }
	virtual inline Vector3 getPosition() { return actor->getGlobalPose().p; }
	virtual inline Vector3 getAcceleration() { return { 0,0,0 }; }
	virtual inline float getInvMass() { if (!isStatic) return rb->getInvMass(); else return 0; }
	virtual inline Vector3 getSize() { return size; }
	virtual Entity* clone() const;
	virtual void onDeath() {};

	virtual void addForce(const Vector3& f) { if (!isStatic) rb->addForce(f); }
	virtual void setInvisible();
	virtual void setRotation(Vector4 rotation);
	void changeUserData(void* data);
	void changeName(std::string name);
	inline std::string getName() { return name; };
protected:
	bool sphereShape, isStatic;
	physx::PxRigidBody* rb;
	physx::PxRigidActor* actor;
	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
	std::string name;
};

