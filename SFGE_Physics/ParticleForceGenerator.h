#pragma once
#include "Particle.h"

namespace SFGE{
	namespace Physics{
		namespace Generators{
			class ParticleForceGenerator{
			public:
				virtual void updateForce(Components::Particle* particle, float duration) = 0;
			};
		}
	}
}