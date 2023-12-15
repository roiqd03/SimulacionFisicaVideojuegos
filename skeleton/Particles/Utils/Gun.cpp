#include "Gun.h"

Gun::Gun() {}

Gun::~Gun() {
	for (auto it : v) {
		delete it;
	}
}

// Cambiar vector a lista con pila de elementos para destruir las particulas 
void Gun::shoot(TypeOfShot t) {
	Projectile* p = nullptr;
	const Vector3 cameraDir = GetCamera()->getDir();
	const Vector3 cameraPos = GetCamera()->getTransform().p;

	switch (t)
	{
		// He multiplicado el radio de todos los proyectiles porque visualmente eran muy pequeños
		case PISTOLA:
			p = new Projectile(0.0035 * 7, {255, 255, 0, 1}, maxParticleLifeTime, this);
			p->setVelocity(cameraDir * 50); // 330 m/s
			p->setInvMass(1/7.84f); // Para que el proyectil se mueva a una velocidad de 50 m/s, su masa debería ser 7.84 Kg,
							   // puesto que la masa de una bala de pistola es de 0.008 Kg
			//p->setGravity({ 0, -0.22f, 0}); // Y su gravedad debería ser -0,22 m/s2 en el eje Y
			p->setDamping(0.99f);
			break;
		case CAÑON:
			p = new Projectile(0.175 * 4, { 0, 0, 0, 1 }, maxParticleLifeTime, this);
			p->setVelocity(cameraDir * 30); // 250 m/s
			p->setInvMass(1/1222.22f); // Para una velocidad de 30 m/s, su masa debería ser 1222,22 Kg, puesto que la masa de 
								  // la bola de cañon es de 17,6 Kg
			//p->setGravity({ 0, -0.14f, 0 }); // Y su gravedad debería ser -0,14 m/s2 en el eje Y
			p->setDamping(0.99f);
			break;
		case TANQUE:
			p = new Projectile(0.06 * 7, { 255, 0, 0, 1 }, maxParticleLifeTime, this);
			p->setVelocity(cameraDir * 150); // 1800 m/s 
			p->setInvMass(1/835.2f); // Para una velocidad de 150 m/s, su masa debería ser 835.2 Kg, puesto que la masa de 
							   // la bala de un tanque es de 5,8 Kg
			//p->setGravity({ 0, -0.068, 0 }); // Y su gravedad debería ser -0,068 m/s2 en el eje Y
			p->setDamping(0.99f);
			break;
	}
	
	p->setPosition(cameraPos + cameraDir);
	v.push_front(p);
	p->setContext(v.begin());
}

void Gun::integrate(float t) {
	for (auto particle : v) {
		particle->integrate(t);
		if (particle->getTime() > maxParticleLifeTime) pushErasedParticles(particle);
	}
}

void Gun::eraseParticles() {
	while (!erased.empty()) {
		auto e = erased.top();
		v.erase(static_cast<Projectile*>(e)->getContext());
		delete e;
		erased.pop();
	}
}

void Gun::pushErasedParticles(Entity* p) {
	erased.push(p);
}

