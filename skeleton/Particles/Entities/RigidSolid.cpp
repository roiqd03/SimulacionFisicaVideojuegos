#include "RigidSolid.h"

RigidSolid::RigidSolid(Vector3 size, Vector4 color, float life_time, bool isStatic, physx::PxPhysics* physics, physx::PxScene* scene) : 
	Entity(size, color, life_time), gPhysics(physics), gScene(scene), isStatic(isStatic) {

	sphereShape = false;
	physx::PxTransform tr({ 0,0,0 }); 
	Vector4 c = color;
	physx::PxShape* shape;
	volume = size.x * size.y * size.z;
	physx::PxBoxGeometry cube(size / 2);
	shape = CreateShape(cube);
	if (!isStatic) {
		rb = physics->createRigidDynamic(tr);
		actor = rb;
		scene->addActor(*rb);
		rb->attachShape(*shape);
		renderItem = new RenderItem(shape, rb, color);
	}
	else {
		actor = physics->createRigidStatic(tr);
		scene->addActor(*actor);
		actor->attachShape(*shape);
		renderItem = new RenderItem(shape, actor, color);
	}

	actor->userData = this;
}

RigidSolid::RigidSolid(float radius, Vector4 color, float life_time, bool isStatic, physx::PxPhysics* physics, physx::PxScene* scene) : 
	Entity(Vector3(radius, radius, radius), color, life_time), gPhysics(physics), gScene(scene), isStatic(isStatic) {

	sphereShape = true;
	Vector4 c = color;
	physx::PxShape* shape;
	volume = (4.0f / 3.0f) * atan(1) * 4 * pow(radius, 3);
	physx::PxSphereGeometry sphere(radius);
	shape = CreateShape(sphere);
	physx::PxTransform tr({ 0,0,0 });
	if (!isStatic) {
		rb = physics->createRigidDynamic(tr);
		scene->addActor(*rb);
		actor = rb;
		rb->attachShape(*shape);
		renderItem = new RenderItem(shape, rb, color);
	}
	else {
		actor = physics->createRigidStatic(tr);
		rb = nullptr;
		scene->addActor(*actor);
		actor->attachShape(*shape);
		renderItem = new RenderItem(shape, actor, color);
	}

	actor->userData = this;
}


RigidSolid::~RigidSolid() {
	if (isStatic)
		static_cast<physx::PxRigidStatic*>(actor)->release();
	else 
		static_cast<physx::PxRigidDynamic*>(rb)->release();
}

void RigidSolid::integrate(double t) {
	Entity::integrate(t);
}

void RigidSolid::setVelocity(Vector3 v) { if(!isStatic) rb->setLinearVelocity(v); }
void RigidSolid::setPosition(Vector3 p) { auto aux = actor->getGlobalPose(); aux.p = p; return actor->setGlobalPose(aux); }

Entity* RigidSolid::clone() const {
	RigidSolid* _rs;
	if (sphereShape)
		_rs = new RigidSolid(size.x, color, life_time, isStatic, gPhysics, gScene);
	else
		_rs = new RigidSolid(size, color, life_time, isStatic, gPhysics, gScene);

	_rs->setPosition(actor->getGlobalPose().p);
	if (!isStatic) {
		_rs->setInvMass(rb->getInvMass());
		_rs->setVelocity(rb->getLinearVelocity());
	}
	return _rs;
}

void RigidSolid::setInvisible() {
	if (isStatic) gScene->removeActor(*actor);
	else gScene->removeActor(*rb);
	Entity::setInvisible();
}

void RigidSolid::setRotation(Vector4 rotation) {
	auto tr = actor->getGlobalPose();
	tr.q.x = rotation.x;
	tr.q.y = rotation.y;
	tr.q.z = rotation.z;
	tr.q.w = rotation.w;
	actor->setGlobalPose(tr);
}

void RigidSolid::changeUserData(void* data) {
	actor->userData = data;
}

void RigidSolid::changeName(std::string name) {
	this->name = name;
}



