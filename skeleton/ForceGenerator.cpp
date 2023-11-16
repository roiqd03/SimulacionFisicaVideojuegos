#include "ForceGenerator.h"
#include <iostream>

ForceGenerator::ForceGenerator(std::string name, double duration) : name(name), duration(duration) {}

bool ForceGenerator::updateTime(double t, bool sum) {
	if(sum) this->t += t;
	return this->t < duration || duration < 0.0;	
}


