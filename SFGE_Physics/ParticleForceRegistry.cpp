#include "ParticleForceRegistry.h"

namespace SFGE{
	namespace Physics{
		namespace Generators{
			void ParticleForceRegistry::add(Components::Particle* particle, ParticleForceGenerator* fg){
				ParticleForceRegistration r;
				r.particle = particle;
				r.fg = fg;
				this->registrations.push_back(r);
			}

			void ParticleForceRegistry::remove(Components::Particle* particle, ParticleForceGenerator* fg){
				ParticleForceRegistration r;
				r.particle = particle;
				r.fg = fg;

				for (int i = 0; i < registrations.size(); i++){
					if (r.fg == registrations[i].fg && r.particle == registrations[i].particle){
						registrations.erase(registrations.begin() + i);
					}
				}
			}

			void ParticleForceRegistry::clear(){
				registrations.clear();
			}

			void ParticleForceRegistry::updateForces(float duration){
				for each (ParticleForceRegistration r in registrations){
					r.fg->updateForce(r.particle, duration);
				}
			}
		}
	}
}