#include "Player.h"
#include "GameManager.h"

Player::Player(physx::PxPhysics* physics, physx::PxScene* scene) : RigidSolid({PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE }, PLAYER_COLOR, -1, false, physics, scene) {
	resetJump();
	actor->setName("PLAYER");
	rb->setMass(PLAYER_MASS);
	static_cast<physx::PxRigidDynamic*>(rb)->setRigidDynamicLockFlags(physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_X | physx::PxRigidDynamicLockFlag::eLOCK_LINEAR_Z | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y | physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	/*physx::PxVec3 v = rb->getMassSpaceInertiaTensor();
	v.x = 0.0f;
	v.y = 0.0f;
	v.z = 0.0f;
	rb->setMassSpaceInertiaTensor(v);*/
	//Entity::setInvMass(1.0f/PLAYER_MASS);
	//physx::PxRigidBodyExt::updateMassAndInertia(*rb, );
}

Player::~Player() {
	GameManager::playerErased(getPosition());
}

void Player::integrate(double t) {
	RigidSolid::integrate(t);
	if (_tryJump) {
		if (grounded) {
			if (abs(rb->getLinearVelocity().y) <= JUMP_OFFSET) {
				GameManager::jump(JUMP_FORCE);
				_tryJump = false;
			}
		}
		else {
			timerJump += t;
			if (timerJump > MAX_TIME_INPUT_STORED) {
				_tryJump = false;
			}
		}
	}
	timer += t;
}
bool Player::resetJump() {
	if (timer > MAX_TIME_GROUNDED) {
		grounded = true;
		yellow_touched = false;
		purple_touched = false;
		timer = 0;
		return true;
	}
	return false;
}


void Player::setInvisible() {
	Entity::setInvisible();
}
