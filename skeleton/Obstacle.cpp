#include "Obstacle.h"

Obstacle::Obstacle(physx::PxPhysics* physics, physx::PxScene* scene, std::vector<std::vector<char>> const& info, float loop_time_after) : Particle(1, {0,0,0,0}, -1), physics(physics), scene(scene), info(info), loop_time_after(loop_time_after) {
	setPosition({ 0, 0, 0 });
	float TRIANGLE_SIZE = OBSTACLE_SIZE / sqrt(2);
	float angle = atan(1) / 2; // 45º / 2
	int k = info.size() - 1, k2 = info[0].size() - 1;
	RigidSolid* rs;
	for (int i = k; i >= 0; --i) {
		for (int j = 0; j <= k2; ++j) {
			if (info[i][j] == '1') {
				rs = new RigidSolid({ OBSTACLE_SIZE, OBSTACLE_SIZE , OBSTACLE_SIZE }, { 0,1,0,1 }, -1, true, physics, scene);
				obstacles.push_front(rs);
				rs->setPosition({ j * OBSTACLE_SIZE, (k - i) * OBSTACLE_SIZE, 0 } );
				rs->changeName("CUADRADO");
			}
			else if (info[i][j] == '2') {
				rs = new RigidSolid({ TRIANGLE_SIZE, TRIANGLE_SIZE, OBSTACLE_SIZE * 0.9f }, { 0,0,1,1 }, -1, true, physics, scene);
				obstacles.push_front(rs);
				rs->setPosition({ j * OBSTACLE_SIZE, (k - i) * OBSTACLE_SIZE - OBSTACLE_SIZE / 2.0f, 0 });
				rs->setRotation({ cos(angle), sin(angle), 0, 0 });
				rs->changeName("TRIANGULO");
			}
			else if (info[i][j] == '3') {
				rs = new RigidSolid(OBSTACLE_SIZE / 2, { 1,1,0,1 }, -1, true, physics, scene);
				obstacles.push_front(rs);
				rs->setPosition({ j * OBSTACLE_SIZE, (k - i) * OBSTACLE_SIZE - OBSTACLE_SIZE * 0.7f, 0 });
				rs->changeName("CIRCULO");
			}
			else if (info[i][j] == '4') {
				rs = new RigidSolid({ OBSTACLE_SIZE, OBSTACLE_SIZE / 2.0f , OBSTACLE_SIZE }, { 0,1,0,1 }, -1, true, physics, scene);
				obstacles.push_front(rs);
				rs->setPosition({ j * OBSTACLE_SIZE, (k - i) * OBSTACLE_SIZE - OBSTACLE_SIZE / 4.0f, 0 });
				rs->changeName("MEDIO_CUADRADO");
			}
		}
	}
	Entity::setInvisible();
}

// Diagonal = OBSTACLE_SIZE
// sqrt(2*pow(lado,2)) = OBSTACLE_SIZE
// pow(lado,2) = pow(OBSTACLE_SIZE, 2) / 2
// lado = OBSTACLE_SIZE / sqrt(2);

Obstacle::~Obstacle() {
	for (auto it : obstacles) {
		delete it;
	}
}

Entity* Obstacle::clone() const {
	return new Obstacle(physics, scene, info, loop_time_after);
}

void Obstacle::integrate(double t) {
	setPosition(getPosition() + getVelocity() * t);
}

void Obstacle::setPosition(Vector3 p){
	Vector3 lastPos = getPosition();
	Particle::setPosition(p);
	Vector3 mov = p - lastPos;
	for (auto it : obstacles) { it->setPosition(it->getPosition() + mov); }
}

void Obstacle::setInvisible() {
	for (auto it : obstacles) { it->setInvisible(); }
}
