#include "ParticleForceRegistry.h"

using namespace::SFGE::Physics::Generators;

void ParticleForceRegistry::add(Components::Particle* particle, ParticleForceGenerator* fg){
	ParticleForceRegistration r;
	r.particle = particle;
	r.fg = fg;
	this->registrations.push_back(r);
}

void ParticleForceRegistry::remove(Components::Particle* particle, ParticleForceGenerator* fg){

}

void ParticleForceRegistry::clear(){
	registrations.clear();
}

void ParticleForceRegistry::updateForces(float duration){
	for each (ParticleForceRegistration r in registrations){
		r.fg->updateForce(r.particle, duration);
	}
}