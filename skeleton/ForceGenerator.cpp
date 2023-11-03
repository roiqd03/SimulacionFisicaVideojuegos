#include "ForceGenerator.h"


ForceGenerator::ForceGenerator(std::string name, double duration) : name(name), duration(duration) {}

bool ForceGenerator::updateTime(double t) {
	this->t += t;
	return t < duration || duration < 0.0;	
}
