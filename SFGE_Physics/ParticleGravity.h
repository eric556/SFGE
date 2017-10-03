#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3.h"

namespace SFGE{
	namespace Physics{
		namespace Generators{
			class ParticleGravity : public ParticleForceGenerator{
				Math::Vector3f gravity;
			public:
				ParticleGravity(const Math::Vector3f& gravity){
					this->gravity = gravity;
				}

				virtual void updateForce(Components::Particle* p, float duration){
					if (!p->hasFiniteMass()) return;
					p->addForce(this->gravity * p->getMass());
				}
			};
		}
	}
}