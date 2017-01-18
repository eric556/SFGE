#pragma once
#include "ParticleForceGenerator.h"
#include <vector>

namespace SFGE{
	namespace Physics{
		namespace Generators{

			class ParticleForceRegistry{
			protected:
				struct ParticleForceRegistration{
					Components::Particle* particle;
					ParticleForceGenerator* fg;
				};

				typedef std::vector<ParticleForceRegistration> Registry;
				Registry registrations;

			public:
				void add(Components::Particle* particle, ParticleForceGenerator* fg);

				void remove(Components::Particle* particle, ParticleForceGenerator* fg);

				void clear();

				void updateForces(float duration);
			};

		}
	}
}